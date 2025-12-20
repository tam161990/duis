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
	$oForm->addElement('submitImg', 'submit', text::get('SAVE'), 'img/btn_saglabat.gif', 'width="70" height="20"');

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
				// Process the uploaded Excel file
				require_once('libs/excel1.7.6/PHPExcel.php');
				
				try
				{
					// Load Excel file
					$objPHPExcel = PHPExcel_IOFactory::load($file['tmp_name']);
					$sheet = $objPHPExcel->getActiveSheet();
					$highestRow = $sheet->getHighestRow();
					
					$successCount = 0;
					$skipCount = 0;
					$errorCount = 0;
					$errors = array();
					
					// Process each row (skip header row)
					for ($row = 2; $row <= $highestRow; $row++)
					{
						// Read data from Excel columns
						// Column A: FAKT_KWOI_KODS (Darbuzņēmēja kods)
						// Column B: FAKT_VV_NUMBER (VV numurs)
						// Column C: FAKT_RBTR_KODS (RBF nodaļa)
						// Column D: FAKT_RLTT_TEXT (Autors)
						// Column E: FAKT_KAKV_KODS (Akta veids)
						// Column F: FAKT_NUM_POSTFIX (Pasūtījuma ID)
						// Column G: FAKT_WORK_TITLE (Darba nosaukums)
						// Column H: FAKT_PIEZIMES (Piezīmes)
						
						$kwoi_kods = trim($sheet->getCell('A' . $row)->getValue());
						$vv_number = trim($sheet->getCell('B' . $row)->getValue());
						$rbtr_kods = trim($sheet->getCell('C' . $row)->getValue());
						$rltt_text = trim($sheet->getCell('D' . $row)->getValue());
						$kakv_kods = trim($sheet->getCell('E' . $row)->getValue());
						$num_postfix = trim($sheet->getCell('F' . $row)->getValue());
						$work_title = trim($sheet->getCell('G' . $row)->getValue());
						$piezimes = trim($sheet->getCell('H' . $row)->getValue());
						
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
						
						// Save to database
						$result = dbProc::saveRbfAkt(
							$kwoi_kods,
							$vv_number,
							$rbtr_kods,
							$rltt_text,
							$kakv_kods,
							$num_postfix,
							$work_title,
							$piezimes
						);
						
						if ($result)
						{
							$successCount++;
						}
						else
						{
							$errorCount++;
							$errors[] = text::get('ERROR_IN_DB_QUERY') . " (Row $row): " . dbProc::getError();
						}
					}
					
					// If any records were successfully imported, save the file
					if ($successCount > 0)
					{
						// Create directory if it doesn't exist
						if (!file_exists(RBF_ACT_FILES_STORE_PATH))
						{
							mkdir(RBF_ACT_FILES_STORE_PATH, 0777, true);
						}
						
						// Generate unique filename
						$originalFileName = $file['name'];
						$generatedFileName = date('Y-m-d_H-i-s') . '_' . uniqid() . '.' . $fileExt;
						$destinationPath = RBF_ACT_FILES_STORE_PATH . '/' . $generatedFileName;
						
						// Copy file to destination
						if (move_uploaded_file($file['tmp_name'], $destinationPath))
						{
							// Save file metadata to database
							$fileSaved = dbProc::saveRbfAktFile($originalFileName, $generatedFileName);
							
							if (!$fileSaved)
							{
								$oForm->addError(text::get('ERROR_SAVING_FILE_INFO'));
							}
						}
						else
						{
							$oForm->addError(text::get('ERROR_SAVING_FILE'));
						}
					}
					
					// Display results
					if ($successCount > 0)
					{
						$oForm->addSuccess(text::get('RBF_IMPORT_SUCCESS') . " $successCount");
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
				}
				catch (Exception $e)
				{
					$oForm->addError(text::get('ERROR_PROCESSING_FILE') . ': ' . $e->getMessage());
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

