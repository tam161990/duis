<?
// RBF Akts Upload Form
if (userAuthorization::isAdmin())
{
	$oLink = new urlQuery();
	$oLink->addPrm(FORM_ID, 'f.adm.s.8');
	$oForm = new Form('frmMain', 'post', $oLink->getQuery());
	unset($oLink);

	// Add file upload field
	$oForm->addElement('uploadfile', 'rbf_akts_file', text::get('RBF_AKTS_FILE'), '', 'accept=".xls,.xlsx"');
	$oForm->addRule('rbf_akts_file', text::get('ERROR_REQUIRED_FIELD'), 'required');

	// Add submit button
	$oForm->addElement('submitImg', 'submit', text::get('SAVE'), 'img/btn_eksportet.gif', 'width="70" height="20"');

	// Process form submission
	if ($oForm->isFormSubmitted())
	{
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
							// Load Excel file
							$objPHPExcel = PHPExcel_IOFactory::load($destinationPath);
							
							// IMPORTANT: Explicitly get Sheet 1 (index 0) for acts data
							// Don't use getActiveSheet() as it might return Sheet 2 if that was active when file was saved
							$sheet = $objPHPExcel->getSheet(0);
							$highestRow = $sheet->getHighestRow();
							
							$successCount = 0;
							$skipCount = 0;
							$errorCount = 0;
							$errors = array();
							
							// Process each row (skip header row)
							for ($row = 2; $row <= $highestRow; $row++)
							{
								// Read data from Excel columns
								// Column A: FAKT_KWOI_KODS (Darbuzņēmēja kods) - REQUIRED
								// Column B: FAKT_VV_NUMBER (VV numurs) - REQUIRED
								// Column C: FAKT_RBTR_KODS (RBF nodaļa) - REQUIRED
								// Column D: FAKT_RLTT_TEXT (Autors) - REQUIRED
								// Column E: FAKT_KAKV_KODS (Akta veids) - REQUIRED
								// Column F: FAKT_NUM_POSTFIX (Pasūtījuma ID) - REQUIRED
								// Column G: FAKT_WORK_TITLE (Darba nosaukums) - REQUIRED
								// Column H: FAKT_SIGNATURE (Paraksts E/P/K) - OPTIONAL
								// Column I: FAKT_PIEZIMES (Piezīmes) - OPTIONAL
								
								// Read data and ensure UTF-8 encoding for Latvian characters
								$kwoi_kods = mb_convert_encoding(trim($sheet->getCell('A' . $row)->getCalculatedValue()), 'UTF-8', 'UTF-8');
								$vv_number = mb_convert_encoding(trim($sheet->getCell('B' . $row)->getCalculatedValue()), 'UTF-8', 'UTF-8');
								$rbtr_kods = mb_convert_encoding(trim($sheet->getCell('C' . $row)->getCalculatedValue()), 'UTF-8', 'UTF-8');
								$rltt_text = mb_convert_encoding(trim($sheet->getCell('D' . $row)->getCalculatedValue()), 'UTF-8', 'UTF-8');
								$kakv_kods = mb_convert_encoding(trim($sheet->getCell('E' . $row)->getCalculatedValue()), 'UTF-8', 'UTF-8');
								$num_postfix = mb_convert_encoding(trim($sheet->getCell('F' . $row)->getCalculatedValue()), 'UTF-8', 'UTF-8');
								$work_title = mb_convert_encoding(trim($sheet->getCell('G' . $row)->getCalculatedValue()), 'UTF-8', 'UTF-8');
								$signature = mb_convert_encoding(trim($sheet->getCell('H' . $row)->getCalculatedValue()), 'UTF-8', 'UTF-8');
								$piezimes = mb_convert_encoding(trim($sheet->getCell('I' . $row)->getCalculatedValue()), 'UTF-8', 'UTF-8');
								
								// Skip empty rows
								if (empty($kwoi_kods) && empty($vv_number) && empty($num_postfix))
								{
									continue;
								}
								
								// Validate required fields
								if (empty($kwoi_kods) || empty($vv_number) || empty($rbtr_kods) || 
									empty($rltt_text) || empty($kakv_kods) || empty($num_postfix) || empty($work_title))
								{
									$errorCount++;
									$errors[] = text::get('ERROR_REQUIRED_FIELD') . " (Row $row)";
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
									$successCount++;
								}
								else
								{
									$errorCount++;
									$errors[] = text::get('ERROR_IN_DB_QUERY') . " (Row $row)";
								}
							}
							
							// Display results for Sheet 1
							if ($successCount > 0)
							{
								$oForm->addSuccess("Akti (Sheet 1) veiksmīgi importēti: $successCount");
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
							}
							
							// STEP 3: Process Sheet 2 (Work data)
							if ($objPHPExcel->getSheetCount() >= 2)
							{
								// Switch to Sheet 2
								$sheet2 = $objPHPExcel->getSheet(1);
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
										// Column F: FADR_NORMA (Normatīvais koeficients / C.st.) - REQUIRED
										// Column G: FADR_PLAN_DATE (Izpildes datums) - OPTIONAL
										
								// Read data and ensure UTF-8 encoding for Latvian characters
								$numPostfix = mb_convert_encoding(trim($sheet2->getCell('A' . $row)->getCalculatedValue()), 'UTF-8', 'UTF-8');
								$rbklShifrs = mb_convert_encoding(trim($sheet2->getCell('B' . $row)->getCalculatedValue()), 'UTF-8', 'UTF-8');
								$mmsKods = mb_convert_encoding(trim($sheet2->getCell('C' . $row)->getCalculatedValue()), 'UTF-8', 'UTF-8');
								$mmsTitle = mb_convert_encoding(trim($sheet2->getCell('D' . $row)->getCalculatedValue()), 'UTF-8', 'UTF-8');
								$status = mb_convert_encoding(trim($sheet2->getCell('E' . $row)->getCalculatedValue()), 'UTF-8', 'UTF-8');
								$norma = trim($sheet2->getCell('F' . $row)->getCalculatedValue());
								$planDateRaw = $sheet2->getCell('G' . $row)->getValue();
										
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
											$norma
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
									
									// Display results for Sheet 2
									if ($sheet2SuccessCount > 0)
									{
										$oForm->addSuccess("Darbi (Sheet 2) veiksmīgi importēti: $sheet2SuccessCount");
									}
									if ($sheet2ErrorCount > 0)
									{
										$oForm->addError("Darbi (Sheet 2) kļūdas: $sheet2ErrorCount");
										foreach ($sheet2Errors as $error)
										{
											$oForm->addError($error);
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

