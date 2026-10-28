<?
// RBF Akts Upload Form

/**
 * Lowercase + remove Latvian diacritics so header matching works even if PHP/Excel uses different UTF-8 or file encoding on the server.
 * All substring needles passed to rbfAktsStrContains should be ASCII-only.
 */
function rbfAktsFoldLvAscii($str)
{
	if ($str === '')
	{
		return '';
	}
	if (function_exists('mb_strtolower'))
	{
		$str = mb_strtolower($str, 'UTF-8');
	}
	else
	{
		$str = strtolower($str);
	}
	static $lv = array(
		'ā' => 'a', 'č' => 'c', 'ē' => 'e', 'ģ' => 'g', 'ī' => 'i',
		'ķ' => 'k', 'ļ' => 'l', 'ņ' => 'n', 'š' => 's', 'ū' => 'u', 'ž' => 'z',
		'Ā' => 'a', 'Č' => 'c', 'Ē' => 'e', 'Ģ' => 'g', 'Ī' => 'i',
		'Ķ' => 'k', 'Ļ' => 'l', 'Ņ' => 'n', 'Š' => 's', 'Ū' => 'u', 'Ž' => 'z',
	);

	return strtr($str, $lv);
}

/**
 * Substring check after Latvian folding; $needle must be ASCII (safe for PHP source encoding on deploy).
 */
function rbfAktsStrContains($haystack, $needle)
{
	$h = rbfAktsFoldLvAscii($haystack);
	$n = rbfAktsFoldLvAscii($needle);
	if ($h === '' || $n === '')
	{
		return false;
	}
	return strpos($h, $n) !== false;
}

/**
 * Normalize Sheet 1 header cell (row 1) for layout fingerprinting.
 */
function rbfAktsExcelHeaderNorm($sheet, $colLetter)
{
	$v = $sheet->getCell($colLetter . '1')->getValue();
	if ($v === null)
	{
		return '';
	}
	if (is_object($v) && method_exists($v, '__toString'))
	{
		$v = (string)$v;
	}
	$v = trim((string)$v);
	if ($v === '')
	{
		return '';
	}
	if (function_exists('mb_strtolower'))
	{
		return mb_strtolower($v, 'UTF-8');
	}
	return strtolower($v);
}

/**
 * Detect when index-0 sheet is the RBF "Darbi" template instead of "Akti".
 */
function rbfAktsExcelSheetLooksLikeWorksSheet($sheet)
{
	$a = rbfAktsExcelHeaderNorm($sheet, 'A');
	$b = rbfAktsExcelHeaderNorm($sheet, 'B');
	$e = rbfAktsExcelHeaderNorm($sheet, 'E');

	if ($a !== '' && rbfAktsStrContains($a, 'uzturesanas'))
	{
		return true;
	}
	if ($b !== '' && rbfAktsStrContains($b, 'kalkulaciju') && rbfAktsStrContains($b, 'sifrs'))
	{
		return true;
	}
	if ($e !== '' && rbfAktsStrContains($e, 'darbibas statusa'))
	{
		return true;
	}
	return false;
}

/**
 * If Sheet 1 matches darbu veidne, acts import must not run (wrong upload type).
 */
function rbfAktsExcelValidateActsSheetLayout($sheet)
{
	if (rbfAktsExcelSheetLooksLikeWorksSheet($sheet))
	{
		return array(
			'ok' => false,
			'message' => text::get('RBF_IMPORT_ACTS_SHEET_LOOKS_LIKE_WORKS')
		);
	}
	return array('ok' => true, 'message' => '');
}

/**
 * Read cell as trimmed string (PHP 8 + PHPExcel: prefer getValue(), same as catalog import).
 */
function rbfAktsExcelCellString($sheet, $cellAddress)
{
	$cell = $sheet->getCell($cellAddress);
	$v = $cell->getValue();
	if ($v === null || (is_string($v) && trim($v) === ''))
	{
		$v = $cell->getCalculatedValue();
	}
	if ($v === null || (is_string($v) && trim($v) === ''))
	{
		try
		{
			$fv = $cell->getFormattedValue();
			if ($fv !== null && !(is_string($fv) && trim($fv) === ''))
			{
				$v = $fv;
			}
		}
		catch (Exception $e)
		{
		}
	}
	if (is_object($v))
	{
		if ($v instanceof PHPExcel_RichText)
		{
			$v = $v->getPlainText();
		}
		elseif (method_exists($v, '__toString'))
		{
			$v = (string)$v;
		}
		else
		{
			$v = '';
		}
	}
	if (is_int($v) || is_float($v))
	{
		$v = (string)$v;
	}

	return trim((string)$v);
}

function rbfAktsExcelReadCol($sheet, $colLetter, $row)
{
	if ($colLetter === '' || $colLetter === null)
	{
		return '';
	}

	return rbfAktsExcelCellString($sheet, $colLetter . $row);
}

/**
 * 10-column (Nodaļa + Daļa) vs legacy 8-column (RBF nodaļa + Autors in D).
 */
function rbfAktsDetectActsColumnMap($sheet)
{
	$dHeader = rbfAktsExcelHeaderNorm($sheet, 'D');
	if ($dHeader !== '' && rbfAktsStrContains($dHeader, 'autor'))
	{
		return array(
			'legacy' => true,
			'cols' => array(
				'kwoi' => 'A', 'vv' => 'B', 'nodala' => 'C', 'dala' => '',
				'author' => 'D', 'kakv' => 'E', 'postfix' => 'F', 'title' => 'G',
				'signature' => '', 'piezimes' => 'H',
			),
		);
	}

	return array(
		'legacy' => false,
		'cols' => array(
			'kwoi' => 'A', 'vv' => 'B', 'nodala' => 'C', 'dala' => 'D',
			'author' => 'E', 'kakv' => 'F', 'postfix' => 'G', 'title' => 'H',
			'signature' => 'I', 'piezimes' => 'J',
		),
	);
}

/**
 * Load .xls / .xlsx with the correct reader.
 * PHPExcel_IOFactory::load() without ext-zip treats .xlsx as CSV and reads garbage.
 *
 * @return PHPExcel|false
 */
function rbfAktsLoadPhpExcelFile($filePath, $fileExt)
{
	$fileExt = strtolower((string)$fileExt);
	if ($fileExt === 'xlsx')
	{
		if (!class_exists('ZipArchive'))
		{
			return false;
		}
		$reader = PHPExcel_IOFactory::createReader('Excel2007');
	}
	elseif ($fileExt === 'xls')
	{
		$reader = PHPExcel_IOFactory::createReader('Excel5');
	}
	else
	{
		return false;
	}
	$reader->setReadDataOnly(true);

	return $reader->load($filePath);
}

/** RBF darbu rindas statusa kodi (2. lapas kolonna E); nedrīkst būt 1. lapas „Autors”. */
function rbfAktsImportedAuthorLooksLikeWorkStatus($rlttText)
{
	static $statuses = array(
		'COMPLETED' => true,
		'PROCESS' => true,
		'NOTHING_TO_DO' => true,
		'CANT_DO' => true,
	);
	$key = strtoupper(trim((string)$rlttText));
	return isset($statuses[$key]);
}

if (userAuthorization::isAdmin())
{
	$oLink = new urlQuery();
	$oLink->addPrm(FORM_ID, 'f.adm.s.8');
	$oForm = new Form('frmMain', 'post', $oLink->getQuery());
	unset($oLink);

	// Add dropdown to select upload type
	$uploadTypeOptions = array(
		'both' => text::get('RBF_UPLOAD_BOTH'),       // "Akti un darbi (2 lapas)"
		'acts' => text::get('RBF_UPLOAD_ACTS_ONLY'),  // "Tikai akti (1 lapa)"
		'works' => text::get('RBF_UPLOAD_WORKS_ONLY') // "Tikai darbi (1 lapa)"
	);
	$oForm->addElement('select', 'upload_type', text::get('RBF_UPLOAD_TYPE'), 'both', '', '', '', $uploadTypeOptions);
	$oForm->addRule('upload_type', text::get('ERROR_REQUIRED_FIELD'), 'required');

	// Add file upload field
	$oForm->addElement('uploadfile', 'rbf_akts_file', text::get('RBF_AKTS_FILE'), '', 'accept=".xls,.xlsx"');
	$oForm->addRule('rbf_akts_file', text::get('ERROR_REQUIRED_FIELD'), 'required');

	// Add submit button
	$oForm->addElement('submitImg', 'submit', text::get('SAVE'), 'img/btn_eksportet.gif', 'width="70" height="20"');

	// Process form submission
	if ($oForm->isFormSubmitted())
	{
		// Get upload type selection
		$uploadType = $oForm->getValue('upload_type'); // 'both', 'acts', or 'works'
		
		if (isset($_FILES['rbf_akts_file']) && $_FILES['rbf_akts_file']['error'] == 0)
		{
			$file = $_FILES['rbf_akts_file'];
			$fileExt = strtolower(pathinfo($file['name'], PATHINFO_EXTENSION));
			
			// Validate file extension
			if (!in_array($fileExt, array('xls', 'xlsx')))
			{
				$oForm->addError(text::get('ERROR_INVALID_FILE_TYPE'));
			}
			else
			{
				// STEP 1: Save file first to get FFLS_ID
				// Create directory if it doesn't exist
				if (!file_exists(RBF_ACT_FILES_STORE_PATH))
				{
					mkdir(RBF_ACT_FILES_STORE_PATH, 0777, true);
				}
				
				// Generate unique filename
				$originalFileName = $file['name'];
				$generatedFileName = date('Y-m-d_H-i-s') . '_' . uniqid() . '.' . $fileExt;
				$destinationPath = RBF_ACT_FILES_STORE_PATH . '/' . $generatedFileName;
				
				// Save file metadata to database first
				$uploadedFileId = dbProc::saveRbfAktFile($originalFileName, $generatedFileName);
				
				if (!$uploadedFileId)
				{
					$oForm->addError(text::get('ERROR_SAVING_FILE_INFO'));
				}
				else
				{
					// Move file to destination
					if (!move_uploaded_file($file['tmp_name'], $destinationPath))
					{
						$oForm->addError(text::get('ERROR_SAVING_FILE'));
					}
					else
					{
						// STEP 2: Process the uploaded Excel file
						require_once('libs/excel1.7.6/PHPExcel.php');
						
						try
						{
							$objPHPExcel = rbfAktsLoadPhpExcelFile($destinationPath, $fileExt);
							if (!$objPHPExcel)
							{
								if ($fileExt === 'xlsx' && !class_exists('ZipArchive'))
								{
									$oForm->addError('PHP paplašinājums „zip” nav ieslēgts — .xlsx failu nevar nolasīt. Ieslēdziet extension=zip php.ini un restartējiet Apache.');
								}
								else
								{
									$oForm->addError(text::get('ERROR_INVALID_FILE_TYPE'));
								}
							}
							else
							{
							$sheet1SuccessMsg = "";
							
							// =========================================================
							// PROCESS ACTS (Sheet 1) - if upload type is 'both' or 'acts'
							// =========================================================
							if ($uploadType == 'both' || $uploadType == 'acts')
							{
								// IMPORTANT: Explicitly get Sheet 1 (index 0) for acts data
								// Don't use getActiveSheet() as it might return Sheet 2 if that was active when file was saved
								$sheet = $objPHPExcel->getSheet(0);
								$layoutCheck = rbfAktsExcelValidateActsSheetLayout($sheet);
								if (!$layoutCheck['ok'])
								{
									$oForm->addError($layoutCheck['message']);
								}
								else
								{
								$highestRow = $sheet->getHighestRow();
								
								$successCount = 0;
								$skipCount = 0;
								$errorCount = 0;
								$errors = array();
								$actsColMap = rbfAktsDetectActsColumnMap($sheet);
								$actsCols = $actsColMap['cols'];
								files::wh_log('[RBF IMPORT DEBUG] Acts layout: ' . ($actsColMap['legacy'] ? 'legacy 8 columns' : 'new 10 columns'));
								files::wh_log('[RBF IMPORT DEBUG] Header A1=' . rbfAktsExcelCellString($sheet, 'A1') . ' D1=' . rbfAktsExcelCellString($sheet, 'D1'));
							
							// Process each row (skip header row)
							for ($row = 2; $row <= $highestRow; $row++)
							{
								$c = $actsCols;
								$kwoi_kods = rbfAktsExcelReadCol($sheet, $c['kwoi'], $row);
								$vv_number = rbfAktsExcelReadCol($sheet, $c['vv'], $row);
								$nodala_kods = rbfAktsExcelReadCol($sheet, $c['nodala'], $row);
								$dala_kods = rbfAktsExcelReadCol($sheet, $c['dala'], $row);
								$rltt_text = rbfAktsExcelReadCol($sheet, $c['author'], $row);
								$kakv_kods = rbfAktsExcelReadCol($sheet, $c['kakv'], $row);
								$num_postfix = rbfAktsExcelReadCol($sheet, $c['postfix'], $row);
								$work_title = rbfAktsExcelReadCol($sheet, $c['title'], $row);
								$signature = rbfAktsExcelReadCol($sheet, $c['signature'], $row);
								$piezimes = rbfAktsExcelReadCol($sheet, $c['piezimes'], $row);
								
								if ($row <= 4)
								{
									files::wh_log("[RBF IMPORT DEBUG] Row $row - KWOI: '$kwoi_kods' VV: '$vv_number' NODALA: '$nodala_kods' DALA: '$dala_kods' POSTFIX: '$num_postfix'");
								}
								
								// Determine which territory code to use (only one should be filled)
								$rbtr_kods = !empty($nodala_kods) ? $nodala_kods : $dala_kods;
								
								// DEBUG: Log determined territory code
								files::wh_log("[RBF IMPORT DEBUG] Row $row - Determined RBTR_KODS: '" . $rbtr_kods . "'");
								
								// Skip empty rows
								if (empty($kwoi_kods) && empty($vv_number) && empty($num_postfix))
								{
									continue;
								}
								
								// Validate required fields (at least one of nodala_kods or dala_kods must be filled)
								if (empty($kwoi_kods) || empty($vv_number) || empty($rbtr_kods) || 
									empty($rltt_text) || empty($kakv_kods) || empty($num_postfix) || empty($work_title))
								{
									$errorCount++;
									$errors[] = text::get('ERROR_REQUIRED_FIELD') . " (Row $row)";
									continue;
								}

								if (rbfAktsImportedAuthorLooksLikeWorkStatus($rltt_text))
								{
									$errorCount++;
									$errors[] = sprintf(
										text::get('RBF_IMPORT_ACT_AUTHOR_WORK_STATUS_ROW'),
										$row,
										$rltt_text
									);
									continue;
								}
								
								// Check if record already exists by FAKT_NUM_POSTFIX
								$existingRecord = dbProc::getRbfAktByPostfix($num_postfix);
								if ($existingRecord)
								{
									$skipCount++;
									continue;
								}
								
								// Save to database with file reference
								// Function signature: saveRbfAkt($kwoiKods, $vvNumber, $rbtrKods, $rlttText, $kakvKods, $numPostfix, $workTitle, $signature = '', $piezimes = '', $fflsId = null)
								
								// DEBUG: Log values before saving to database
								files::wh_log("[RBF IMPORT DEBUG] Row $row - Saving to DB:");
								files::wh_log("[RBF IMPORT DEBUG]   KWOI_KODS: '" . $kwoi_kods . "'");
								files::wh_log("[RBF IMPORT DEBUG]   VV_NUMBER: '" . $vv_number . "'");
								files::wh_log("[RBF IMPORT DEBUG]   RBTR_KODS: '" . $rbtr_kods . "'");
								files::wh_log("[RBF IMPORT DEBUG]   NUM_POSTFIX: '" . $num_postfix . "'");
								
								$result = dbProc::saveRbfAkt(
									$kwoi_kods,
									$vv_number,
									$rbtr_kods,
									$rltt_text,
									$kakv_kods,
									$num_postfix,
									$work_title,
									$signature,        // 8th param (optional)
									$piezimes,         // 9th param (optional)
									$uploadedFileId    // 10th param (optional) - CORRECTED
								);
								
								if ($result)
								{
									files::wh_log("[RBF IMPORT DEBUG] Row $row - Successfully saved");
									$successCount++;
								}
								else
								{
									files::wh_log("[RBF IMPORT DEBUG] Row $row - FAILED to save");
									$errorCount++;
									$errors[] = text::get('ERROR_IN_DB_QUERY') . " (Row $row)";
								}
							}
							
								// Display results for Sheet 1
								if ($successCount > 0)
								{
									$oForm->addSuccess("Akti (Sheet 1) veiksmīgi importēti: $successCount");
									$sheet1SuccessMsg = "Akti (Sheet 1) veiksmīgi importēti: $successCount";
								}
								if ($skipCount > 0)
								{
									$oForm->addSuccess(text::get('RBF_IMPORT_SKIPPED') . " $skipCount");
								}
								if ($errorCount > 0)
								{
									$oForm->addError(text::get('RBF_IMPORT_ERRORS') . " $errorCount");
									foreach ($errors as $error)
									{
										$oForm->addError($error);
									}
									// Don't exit here if we also need to process works
									if ($uploadType == 'acts') {
										exit;
									}
								}
								if ($successCount === 0 && $errorCount === 0 && $skipCount === 0 && $highestRow >= 2)
								{
									$oForm->addError('Nav atrasti aktu dati pirmajā lapā. Pārbaudiet, ka fails ir Excel (.xls/.xlsx), pirmajā rindā ir virsraksti, un dati sākas no 2. rindas.');
								}
								}
							} // End of Acts processing
							
							// =========================================================
							// PROCESS WORKS (Sheet 2) - if upload type is 'both' or 'works'
							// =========================================================
							if (($uploadType == 'both' || $uploadType == 'works') && 
								(($uploadType == 'works') || ($objPHPExcel->getSheetCount() >= 2)))
							{
								// Get correct sheet index based on upload type
								// If 'works' only, it's in Sheet 1 (index 0), otherwise Sheet 2 (index 1)
								$sheetIndex = ($uploadType == 'works') ? 0 : 1;
								$sheet2 = $objPHPExcel->getSheet($sheetIndex);
								$highestRow2 = $sheet2->getHighestRow();
								
								// Empty the rbf_akta_darbi_tmp table before inserting new data
								if (!dbProc::truncateRbfAktaDarbiTmp())
								{
									$oForm->addError('Kļūda iztīrot rbf_akta_darbi_tmp tabulu');
								}
								else
								{
									$sheet2SuccessCount = 0;
									$sheet2ErrorCount = 0;
									$sheet2Errors = array();
									
									// Process each row in Sheet 2 (skip header row)
									for ($row = 2; $row <= $highestRow2; $row++)
									{
										// Read data from Excel columns
										// Column A: FADR_NUM_POSTFIX (Uzturēšanas darba numurs) - REQUIRED
										// Column B: FADR_RBKL_SHIFRS (Kalkulāciju kategorijas šifrs) - REQUIRED
										// Column C: FADR_MMS_KODS (MMS nosacījums ID) - REQUIRED
										// Column D: FADR_MMS_TITLE (MMS darbība/Nosacījums) - REQUIRED
										// Column E: FADR_STATUS (Darbības status) - REQUIRED
										// Column F: FADR_MERVIENIBA (Mērvienība) - OPTIONAL
										// Column G: FADR_APJOMS (Apjoms) - OPTIONAL
										// Column H: FADR_CST_NORMA (C.st. norma) - OPTIONAL
										// Column I: FADR_NORMA (Normatīvais koeficients / C.st.) - REQUIRED
										// Column J: FADR_PLAN_DATE (Izpildes datums) - OPTIONAL
										
										$numPostfix = rbfAktsExcelCellString($sheet2, 'A' . $row);
										$rbklShifrs = rbfAktsExcelCellString($sheet2, 'B' . $row);
										$mmsKods = rbfAktsExcelCellString($sheet2, 'C' . $row);
										$mmsTitle = rbfAktsExcelCellString($sheet2, 'D' . $row);
										$status = rbfAktsExcelCellString($sheet2, 'E' . $row);
										$mervieniba = rbfAktsExcelCellString($sheet2, 'F' . $row);
										$apjoms = rbfAktsExcelCellString($sheet2, 'G' . $row);
										$cstNorma = rbfAktsExcelCellString($sheet2, 'H' . $row);
										$norma = rbfAktsExcelCellString($sheet2, 'I' . $row);
										$planDateCell = $sheet2->getCell('J' . $row);
										$planDateRaw = $planDateCell->getValue();
										if ($planDateRaw === null || $planDateRaw === '')
										{
											$planDateRaw = $planDateCell->getCalculatedValue();
										}
										
										
										// Skip empty rows
										if (empty($numPostfix) && empty($rbklShifrs) && empty($mmsKods))
										{
											continue;
										}
										
										// Validate required fields
										if (empty($numPostfix) || empty($rbklShifrs) || empty($mmsKods) || 
											empty($mmsTitle) || empty($status) || empty($norma))
										{
											$sheet2ErrorCount++;
											$sheet2Errors[] = text::get('ERROR_REQUIRED_FIELD') . " Sheet 2 (Row $row)";
											continue;
										}
										
										// Convert date if needed
										$planDate = null;
										if (!empty($planDateRaw))
										{
											// Check if it's already a datetime object
											if ($planDateRaw instanceof DateTime)
											{
												$planDate = $planDateRaw->format('Y-m-d H:i:s');
											}
											// Check if it's an Excel date serial number
											elseif (is_numeric($planDateRaw))
											{
												$planDate = PHPExcel_Style_NumberFormat::toFormattedString($planDateRaw, 'YYYY-MM-DD HH:MM:SS');
											}
											// Try to parse as string date
											else
											{
												$timestamp = strtotime($planDateRaw);
												if ($timestamp !== false)
												{
													$planDate = date('Y-m-d H:i:s', $timestamp);
												}
											}
										}
										
										// Save to database
										$result = dbProc::saveRbfAktaDarbs(
											$numPostfix,
											$rbklShifrs,
											$mmsKods,
											$mmsTitle,
											$status,
											$planDate,
											$norma,
											!empty($mervieniba) ? $mervieniba : null,
											!empty($apjoms) ? $apjoms : null,
											!empty($cstNorma) ? $cstNorma : null
										);
										
										if ($result)
										{
											$sheet2SuccessCount++;
										}
										else
										{
											$sheet2ErrorCount++;
											$sheet2Errors[] = text::get('ERROR_IN_DB_QUERY') . " Sheet 2 (Row $row)";
										}
									}
									
									// Display results for Works
									if ($sheet2SuccessCount > 0)
									{
										$sheetLabel = ($uploadType == 'works') ? 'Darbi' : 'Darbi (Sheet 2)';
										$combinedMsg = !empty($sheet1SuccessMsg) ? $sheet1SuccessMsg . "<br>" : "";
										$oForm->addSuccess($combinedMsg . "$sheetLabel veiksmīgi importēti: $sheet2SuccessCount");
									}
									if ($sheet2ErrorCount > 0)
									{
										$sheetLabel = ($uploadType == 'works') ? 'Darbi' : 'Darbi (Sheet 2)';
										$oForm->addError("$sheetLabel kļūdas: $sheet2ErrorCount");
										foreach ($sheet2Errors as $error)
										{
											$oForm->addError($error);
										}
									}
								}
							}
							}
						}
						catch (Exception $e)
						{
							$oForm->addError(text::get('ERROR_PROCESSING_FILE') . ': ' . $e->getMessage());
						}
					}
				}
			}
		}
		else
		{
			$oForm->addError(text::get('ERROR_FILE_UPLOAD'));
		}
	}

	$oForm->makeHtml();
	include('f.adm.s.8.tpl');
}
else
{
	RequestHandler::showErrorAndDie(text::get('ERROR_NOT_PERMISSION'));
}
?>

