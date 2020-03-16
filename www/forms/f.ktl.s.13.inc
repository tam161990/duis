<?
// Created by Tatjana Fedorkova
$userId = userAuthorization::getUserId();
$isEdUser = dbProc::isUserInRole($userId, ROLE_ED_USER);
if (userAuthorization::isAdmin() || $isEdUser )
{

    $oLink=new urlQuery();
    $oLink->addPrm(FORM_ID, 'f.ktl.s.13');
    $oLink->addPrm('isNew', '1');
    $oForm = new Form('frmMain','post',$oLink->getQuery());
    unset($oLink);

    // get catalog import list
    $catalog=array();
    $catalog['']=text::get('EMPTY_SELECT_OPTION');

    $res=dbProc::getKrfkName(KRFK_IMPORT);
    if (is_array($res))
    {
       	foreach ($res as $row)
      	{
      	   if (userAuthorization::isAdmin() && $isEdUser && 
		        ($row['nosaukums'] == 'MMS_WORKS' || $row['nosaukums'] == 'KALKULATION_TR' || $row['nosaukums'] == 'KALKULATION') 
	        )
           {
      		   $catalog[$row['nosaukums']]=$row['nozime'];
           }
           if (userAuthorization::isAdmin() && !$isEdUser)
           {
      		   $catalog[$row['nosaukums']]=$row['nozime'];
           }
       	}
    }
    unset($res);

    // get kaklulation catalog import options list
    $options=array();
    $options['']=text::get('EMPTY_SELECT_OPTION');

    $res=dbProc::getKrfkName(KRFK_IMPORT_K);
    if (is_array($res))
    {
       	foreach ($res as $row)
      	{
      	   $options[$row['nosaukums']]=$row['nozime'];
       	}
    }
    unset($res);

    // if operation is success, show success message and redirect top frame
    if (reqVar::get('successMessage'))
    {
    	$oForm->addSuccess(reqVar::get('successMessage'));
    }

    $oForm -> addElement('select', 'catalog',  text::get('CATALOG'),'', 'onchange="setImportColumnVisibility();"'.((!userAuthorization::isAdmin() && $isEdUser)?' disabled' : ''), '', '', $catalog);
    $oForm -> addRule('catalog', text::get('ERROR_REQUIRED_FIELD'), 'required');

    $oForm -> addElement('uploadfile', 'fileName', text::get('FILE'), '','class="flex"');

    $oForm -> addElement('select', 'options',  '', '', ' disabled', '', '', $options);

    $oForm -> addRule('fileName', text::get('ERROR_REQUIRED_FIELD'), 'required');
    if(userAuthorization::isAdmin())
    {
        $oForm -> addElement('submitImg', 'submit', text::get('DO_IMPORT'), 'img/btn_import.gif', 'width="70" height="20"'.((!userAuthorization::isAdmin() && $isEdUser)?' disabled' : ''));
    }

    if ($oForm -> isFormSubmitted())
    {
        $file = false;
        $r = true;
        $r2 = true;
        $mms_exists = false;

        $checkRequiredFields = false;
        if ($oForm -> getValue('catalog'))
        {
    	    $checkRequiredFields = true;
        }
        if ($checkRequiredFields)
        {
              // save file
          if(files::isUploadFile('fileName'))
          {
              // chek file type
              // chek file type
              if(files::isUploadFileOfExt('fileName', 'csv'))
              { 
                  $file = files::saveFileToStore('fileName');
                  // if operation is success
                  if($file!=false)
                  {                  
                      
                      if($oForm -> getValue('catalog') == 'MMS_WORKS')
                      {
                          $mms_exists = dbProc::is_mms_exists();
                      }           
                      if($r)
                      {  
                          $handle = fopen($file, "r");
                          $r2 = true;
                          $idx = 0;
                          while($data = fgetcsv($handle))
                          {
                              $idx ++;
                              if($idx == 1) {
                                continue;
                              }
                              switch (  $oForm -> getValue('catalog'))
                              { 
                                
                                // catalog Kalkulacija
                                case 'KALKULATION':
                                  $r2 = dbProc::saveCalculationFromCsv($data, $userId);
                                  break;
                                // catalog MMS-Kalkulacija
                                case 'MMS_KALKULATION':
                                  $r2 = dbProc::saveMmsCalculationFromCsv($data, $userId);
                                  break;
                                // catalok Kalkulācija - Materiāli
                                case 'KALKULATION_MATERIAL':
                                  $r2 = dbProc::saveCalculationMaterialFromCsv($data, $userId);
                                  break;
                                // catalog MMS Works
                                case 'MMS_WORKS':
                                  $r2 = dbProc::saveMmsFromCsv($data, $userId, $mms_exists);                                     
                                break;                                              
                                // catalog Materials
                                case 'MATERIAL':
                                  $r2 = dbProc::saveMaterialFromCsv($data, $userId);
                                  break;  
                                // ED  
                                case 'EDAREA':
                                  $r2 = dbProc::saveEDAreaFromCsv($data, $userId);
                                  break; 
                                // catalog saskaņotāji
                              case 'HARMONIZED':
                                $r2 = dbProc::saveHarmonizedFromCsv($data, $userId);
                                break; 
                                  
                              }
                              if($r2 === false )
                              {
                                  files::eraseFileFromStore2($file);
                                  break ;
                              }                                                                
                          } 
                          fclose($handle);   
                      } 
                      if($oForm -> getValue('catalog') == 'MMS_WORKS')
                      {
                        //$r2 = dbProc::processAutoActs($userId);
                      }
                  }
                  
                  // if operation was compleated succefully, show success mesage and redirect current frame
                  if($r !== false && $r2 !== false)
                  {
                    if($oForm -> getValue('catalog') == 'MMS_WORKS' )
                    {
                      $oLink=new urlQuery();
                      $oLink->addPrm('isNew', '1');
                      $oLink->addPrm(FORM_ID, 'f.ktl.s.13');
                      $oLink->addPrm('successMessage', text::get('IMPORT_SUCCESS'));
                      RequestHandler::makeRedirect($oLink->getQuery());
                    }
                    else
                    {
                      // list
                      $oLink=new urlQuery();
                      $oLink->addPrm('isNew', '1');
                      switch (  $oForm -> getValue('catalog'))
                        {
                          
                          // catalog Materiali
                          case 'MATERIAL':
                            $oLink->addPrm(FORM_ID, 'f.ktl.s.1');
                              break;
                          // catalog Kalulācija
                          case 'KALKULATION':
                            $oLink->addPrm(FORM_ID, 'f.ktl.s.10');
                              break;
                          // catalog MMS-Kalulācija
                          case 'MMS_KALKULATION':
                            $oLink->addPrm(FORM_ID, 'f.ktl.s.20');
                              break;
                          // catalog Kalulācija-Materiāli
                          case 'KALKULATION_MATERIAL':
                            $oLink->addPrm(FORM_ID, 'f.ktl.s.21');
                              break;            
                          // ED
                          case 'EDAREA':
                            $oLink->addPrm(FORM_ID, 'f.ktl.s.5');
                              break; 
                          // catalog saskaņotāji
                          case 'HARMONIZED':
                            $oLink->addPrm(FORM_ID, 'f.ktl.s.4');
                            break;                            
                          
                      }
                      $listLink=$oLink ->getQuery();
                      unset($oLink);
                      // add/edit
                      $oLink=new urlQuery();
                      switch (  $oForm -> getValue('catalog'))
                       {
                          
                          // catalog Material
                          case 'MATERIAL':
                            $oLink->addPrm(FORM_ID, 'f.ktl.s.1');
                              break;
                          // catalog Kalulācija
                          case 'KALKULATION':
                            $oLink->addPrm(FORM_ID, 'f.ktl.s.10');
                              break;
                          // catalog MMS-Kalulācija
                          case 'MMS_KALKULATION':
                            $oLink->addPrm(FORM_ID, 'f.ktl.s.20');
                              break;
                          // catalog Kalulācija-Materiāli
                          case 'KALKULATION_MATERIAL':
                            $oLink->addPrm(FORM_ID, 'f.ktl.s.21');
                              break;   
                          // ED
                          case 'EDAREA':
                            $oLink->addPrm(FORM_ID, 'f.ktl.s.5');
                              break;   
                          // catalog saskaņotāji
                          case 'HARMONIZED':
                            $oLink->addPrm(FORM_ID, 'f.ktl.s.4');
                            break;                    
                          
                      }
                      $oLink->addPrm('editMode', '1');
                      $editLink = $oLink->getQuery();
                      unset($oLink);

                      $oForm->addElement('static','jsRefresh2','','
                      <script>
                          parent["frameTop"].enableFrameControl();
                          window.top.enableResize();
                          window.top.min(0);
                          window.top.normal();
                          reloadFrame(1,"'.$listLink.'");
                          reloadFrame(2,"'.$editLink.'");
                          reloadFrame(3,"");
                      </script>
                      ');
                      }
                  }
                  else
                  {
                      files::eraseFileFromStore2($file);
                      $oForm->addError(text::get('ERROR_IMPORT_NOT_SUCCESS'));
                  }
                }
               /* else if(files::isUploadFileOfTYpe('fileName', 'application/vnd.ms-excel'))
                {
                    $file = files::saveFileToStore('fileName');
                    // if operation is success
    				        if($file!=false)
                    {
                         $objReader = PHPExcel_IOFactory::createReader('Excel5');
                         $objReader->setReadDataOnly(true);
                         $objPHPExcel = $objReader->load($file);
                         $objWorksheet = $objPHPExcel->getActiveSheet();

                         switch (  $oForm -> getValue('catalog'))
                         {
                            // catalog Customers
                            case 'EDAREA':

                                $r = dbProc::createEDAreaTempTable();
                                if($r === false)
                                {
                                  dbProc::deleteEDAreaTable(false);
                                  files::eraseFileFromStore2($file);
                                }

                                $j = 0;
                                foreach ($objWorksheet->getRowIterator() as $row)
                                {
                                    $cellIterator = $row->getCellIterator();
                                    $cellIterator->setIterateOnlyExistingCells(true);

                                    $i = 0;
                                    foreach ($cellIterator as $cell)
                                    {
                                      if(!is_null($cell))
                                      {
                                          $i++;
                                          $j++;
                                          if($j == 1)
                                              break 1;
                                          if($i == 1) $code =  $cell->getValue(); // Kods
                                          if($i == 2) $region = $cell->getValue(); // Reģions
                                          if($i == 3) $title = $cell->getValue();// Nosaukums.
                                          if($i == 4) $section = $cell->getValue();// ED nodaļa
                                          if($i == 5) $element = $cell->getValue();// Is stihija

                                       }
                                    }
                                    // save ED record
                                    if($j > 1)
                                    {
                                      $r2=dbProc::saveEDArea(false, $region, $code, $title, 1, $section, $element, false);
                                      if($r2 === false )
                                      {
                                          dbProc::deleteEDAreaTable(false);
                                          files::eraseFileFromStore2($file);
                                          break 2;
                                      }
                                    }
                                  }
                                  // ja visi ieraksti veiksmigi importēti, tad jaizdzest veco tabulu un japarsauc jaunizveidotu
                                  if($r2)
                                  {
                                      $r3 = dbProc::deleteEDAreaTable();

                                      $r4 = dbProc::renameEDAreaTable();
                                  }
                                  if($r === false || $r2 === false || $r3 === false || $r4 === false)
                                  {
                                      dbProc::deleteEDAreaTable(false);
                                  }
                               break;
			        // statusa imports
                            	case 'KALKULATION_STATUSS':
                            $r2 = true;
                                    $r3 = true;
                                  $r4= true;
                                        $j = 0;
                       		foreach ($objWorksheet->getRowIterator() as $row)
                       		{
                       			$cellIterator = $row->getCellIterator();
                       			$cellIterator->setIterateOnlyExistingCells(true);
					                  $aktivs = '';
                       			$i = 0;
                       			foreach ($cellIterator as $cell)
                       			{
                       				 if(!is_null($cell))
                       				 {
                       					$i++;
                       					$j++;
	              					if($j == 1)
                      						break 1;
                      					if($i == 1) $id =  $cell->getValue(); // Kalk ID  
                                          		if($i == 2) $trase = $cell->getValue();// Ir trase
                      					if($i == 3) 
                                {
                                  $aktivs = $cell->getValue();// Ir aktivs							
                                  echo '-'.$aktivs;
                                  
                                }
                      				  }
                       			}
					
                                    	// update kalkulaciju
                                    	if($j > 1)
                                    	{
                                        if( is_numeric($aktivs)  && ( $aktivs == 0 || $aktivs == 1))	
                                        { 
                                          echo $aktivs;
                                            $r=dbProc::setCalkulationStatuss($id, $trase, $aktivs);
                                              if($r === false )
                                              {
                                                  break 1;
                                              }
                                          }
                                        }
                                  }
                                  break;

                            // catalog Kalkulacija
                            case 'KALKULATION':
                                $style = $oForm -> getValue('options');
                                if($style == 'INSERT')
                                {
                                  $r = dbProc::createCalculationTempTable();
                                  if($r === false)
                                  {
                                    dbProc::deleteCalculationTable(false);
                                    files::eraseFileFromStore2($file);
                                  }
                                }
                                $j = 0;
                                foreach ($objWorksheet->getRowIterator() as $row)
                                {
                                    $cellIterator = $row->getCellIterator();
                                    $cellIterator->setIterateOnlyExistingCells(true);

                                    $i = 0;
                                    $cl1 = 0;
                                    $cl2 = 0;
                                    $cl3 = 0;
                                    $cl4 = 0;
                                    $cl5 = 0;
                                    $cl6 = 0;
                                    $cl7 = 0;
                                    $cl8 = 0;
                                    $cl9 = 0;
                                    $cl10 = 0;
                                    $fizRadijums = ' ';
                                    $koeficent = 1;
                                    $element = 0;
				                            $is_active = 0;
                                    foreach ($cellIterator as $cell)
                                    {
                                      if(!is_null($cell))
                                      {
                                          $i++;
                                          $j++;

                                          if($j == 1)
                                              break 1;
                                           if($i == 1) $code =  $cell->getValue(); // code
                                          if($i == 2) $chipher = $cell->getValue();// chipher
                                          if($i == 3) $title = $cell->getValue();// Title
                                          if($i == 4) $measure = $cell->getValue();// Mervieniba
                                          if($i == 5) $description = $cell->getValue();// Description
                                          if($i == 6) $fizRadijums = $cell->getValue();// Fiziskais rādītājs
                                          if($i == 7) $worker = $cell->getValue();// Darbuzņēmējs
                                          if($i == 8) $contract = $cell->getValue();// Līgums
                                          if($i == 9) $edArea = $cell->getValue();// ED nodaļa
                                          if($i == 10) $planPrice = $cell->getValue();// Plāna cena
                                          if($i == 11) $notPlanPrice = $cell->getValue();// Neplāna cena
                                          if($i == 12) $koeficent = $cell->getValue();//Koeficents
                                          if($i == 13) $element  = $cell->getValue();// Is stihija
					    if($i == 14) $is_active  = $cell->getValue();// Is aktivs
                                          if($i == 15) $cl1 = $cell->getValue();// Papild kolonna
                                          if($i == 16) $cl2 = $cell->getValue();// Papild kolonna
                                          if($i == 17) $cl3 = $cell->getValue();// Papild kolonna
                                          if($i == 18) $cl4 = $cell->getValue();// Papild kolonna
                                          if($i == 19) $cl5 = $cell->getValue();// Papild kolonna
                                          if($i == 20) $cl6 = $cell->getValue();// Papild kolonna
                                          if($i == 21) $cl7 = $cell->getValue();// Papild kolonna
                                          if($i == 22) $cl8 = $cell->getValue();// Papild kolonna
                                          if($i == 23) $cl9 = $cell->getValue();// Papild kolonna
                                          if($i == 24) $cl10 = $cell->getValue();// Papild kolonna

                                       }
                                    }
                                    // save kalkulācijas record
                                    if($j > 1)
                                    {
                                      $r2=dbProc::saveCalculation2($chipher, $code, $title, $description,  $measure, $is_active, $fizRadijums, $koeficent, $worker, $edArea, $planPrice, $notPlanPrice, $element, $contract,
                                        ($style == 'INSERT') ? false : true,
                                        $cl1, $cl2, $cl3, $cl4, $cl5, $cl6, $cl7, $cl8, $cl9, $cl10);
                                      if($r2 === false )
                                      {
                                        if($style == 'INSERT')
                                            dbProc::deleteCalculationTable(false);

                                        files::eraseFileFromStore2($file);
                                        break 2;
                                      }
                                    }
                                  }
                                  // ja visi ieraksti veiksmigi importēti, tad jaizdzest veco kalkulācijas tabulu un japarsauc jaunizveidotu
                                if($style == 'INSERT')
                                {
                                  if($r2)
                                  {
                                     $r3 = dbProc::deleteCalculationTable();

                                      $r4 = dbProc::renameCalculationTable();
                                  }
                                  if($r === false || $r2 === false || $r3 === false || $r4 === false)
                                  {
                                      dbProc::deleteCalculationTable(false);
                                  }
                                }
                                else
                                {
                                  $r = true;
                                  $r3 = true;
                                  $r4 = true;
                                }
                               break;
                            // catalog TRASES Kalkulacija
                            case 'KALKULATION_TR':
                                $style = $oForm -> getValue('options');
                                if($style == 'INSERT')
                                {
                                  $r = dbProc::createCalculationTrTempTable();
                                  if($r === false)
                                  {
                                    dbProc::deleteCalculationTrTable(false);
                                    files::eraseFileFromStore2($file);
                                  }
                                }
                                $j = 0;
                                foreach ($objWorksheet->getRowIterator() as $row)
                                {
                                    $cellIterator = $row->getCellIterator();
                                    $cellIterator->setIterateOnlyExistingCells(true);

                                    $i = 0;
                                    $fizRadijums = ' ';
                                    $description = ' ';
                                    $element = 0;
                                                                         $is_active = 0;
                                    foreach ($cellIterator as $cell)
                                    {
                                      if(!is_null($cell))
                                      {
                                          $i++;
                                          $j++;

                                          if($j == 1)
                                              break 1;
                                          if($i == 1) $code =  $cell->getValue(); // code
                                          if($i == 2) $chipher = $cell->getValue();// chipher
                                          if($i == 3) $title = $cell->getValue();// Title
                                          if($i == 4) $measure = $cell->getValue();// Mervieniba
                                          if($i == 5) $fizRadijums = $cell->getValue();// Fiziskais rādītājs
                                          if($i == 6) $worker = $cell->getValue();// Darbuzņēmējs
                                          if($i == 7) $contract = $cell->getValue();// Līgums
                                          if($i == 8) $edArea = $cell->getValue();// ED nodaļa
                                          if($i == 9) $planPrice = $cell->getValue();// Plāna cena
                                          if($i == 10) $notPlanPrice = $cell->getValue();// Neplāna cena
                                          if($i == 11) $element  = $cell->getValue();// Is stihija					
					    if($i == 12) $is_active  = $cell->getValue();// Is aktivs	
                                          if($i == 13) $description = $cell->getValue();// Description


                                       }
                                    }
                                    // save kalkulācijas record
                                    if($j > 1)
                                    {
                                      $r2=dbProc::saveCalculationTr2($chipher, $code, $title, $description,  $measure, $is_active, $fizRadijums,  $worker, $edArea, $planPrice, $notPlanPrice, $element, $contract,
                                        ($style == 'INSERT') ? false : true);
                                      if($r2 === false )
                                      {
                                        if($style == 'INSERT')
                                            dbProc::deleteCalculationTrTable(false);

                                        files::eraseFileFromStore2($file);
                                        break 2;
                                      }
                                    }
                                  }
                                  // ja visi ieraksti veiksmigi importēti, tad jaizdzest veco kalkulācijas tabulu un japarsauc jaunizveidotu
                                if($style == 'INSERT')
                                {
                                  if($r2)
                                  {
                                      $r3 = dbProc::deleteCalculationTrTable();

                                      $r4 = dbProc::renameCalculationTrTable();
                                  }
                                  if($r === false || $r2 === false || $r3 === false || $r4 === false)
                                  {
                                      dbProc::deleteCalculationTrTable(false);
                                  }
                                }
                                else
                                {
                                  $r = true;
                                  $r3 = true;
                                  $r4 = true;
                                }
                               break;
                            // catalog saskaņotāji
                            case 'HARMONIZED':
                                $style = $oForm -> getValue('options');
                                 $r = dbProc::createHarmonizedTempTable();
                                  if($r === false)
                                  {
                                    dbProc::deleteHarmonizedTablee(false);
                                    files::eraseFileFromStore2($file);
                                  }
                                $j = 0;
                                foreach ($objWorksheet->getRowIterator() as $row)
                                {
                                    $cellIterator = $row->getCellIterator();
                                    $cellIterator->setIterateOnlyExistingCells(true);

                                    $i = 0;

                                    foreach ($cellIterator as $cell)
                                    {
                                      if(!is_null($cell))
                                      {
                                          $i++;
                                          $j++;

                                          if($j == 1)
                                              break 1;
                                          if($i == 1) $code =  $cell->getValue(); // ed code
                                          if($i == 2) $name = $cell->getValue();// name
                                          if($i == 3) $surname = $cell->getValue();// surname
                                          if($i == 4) $position = $cell->getValue();// position
                                          if($i == 5) $department = $cell->getValue();// saskanotaji
                                       }
                                    }
                                    // save saskaņotāja record
                                    if($j > 1)
                                    {
                                      $r2=dbProc::saveHarmonized2($name,$surname,$code,$position,$department, false);

                                      if($r2 === false )
                                      {
                                        dbProc::deleteHarmonizedTable(false);
                                        files::eraseFileFromStore2($file);
                                        break 2;
                                      }
                                    }
                                  }
                                  // ja visi ieraksti veiksmigi importēti, tad jaizdzest veco kalkulācijas tabulu un japarsauc jaunizveidotu
                               if($r2)
                                {
                                    $r3 = dbProc::deleteHarmonizedTable();

                                    $r4 = dbProc::renameHarmonizedTable();
                                }
                                if($r === false || $r2 === false || $r3 === false || $r4 === false)
                                {
                                    dbProc::deleteHarmonizedTable(false);
                                }
                               break;
                            // catalog MMS Works
                            case 'MMS_WORKS':
                                /*
                                $r = dbProc::createMMSWorkTempTable();
                                if($r === false)
                                {
                                  dbProc::deleteMMSWorkTable(false);
                                  files::eraseFileFromStore2($file);
                                }

                                $j = 0;
                                foreach ($objWorksheet->getRowIterator() as $row)
                                {
                                    $cellIterator = $row->getCellIterator();
                                    $cellIterator->setIterateOnlyExistingCells(true);

                                    $i = 0;
                                    foreach ($cellIterator as $cell)
                                    {
                                      if(!is_null($cell))
                                      {
                                          $i++;
                                          $j++;
                                          if($j == 1)
                                              break 1;
                                          if($i == 1) $title =  $cell->getValue(); // Title
                                          if($i == 2)  $code = $cell->getValue();// Code

                                       }
                                    }
                                    // save customer record
                                    if($j > 1)
                                    {
                                      $r2=dbProc::saveMMSWork(false, $code, $title, 0, false);
                                      if($r2 === false )
                                      {
                                          dbProc::deleteMMSWorkTable(false);
                                          files::eraseFileFromStore2($file);
                                          break 2;
                                      }
                                    }
                                  }
                                  // ja visi ieraksti veiksmigi importēti, tad jaizdzest veco personāls tabulu un japarsauc jaunizveidotu
                                  if($r2)
                                  {
                                      $r3 = dbProc::deleteMMSWorkTable();

                                      $r4 = dbProc::renameMMSWorkTable();
                                  }
                                  if($r === false || $r2 === false || $r3 === false || $r4 === false)
                                  {
                                      dbProc::deleteMMSWorkTable(false);
                                  }
                                  */
                                /*$r = true;
                                $r3 = true;
                                $r4 = true;

                                $j = 0;
                                foreach ($objWorksheet->getRowIterator() as $row)
                                {
                                    $cellIterator = $row->getCellIterator();
                                    $cellIterator->setIterateOnlyExistingCells(false);

                                    $i = 0;
                                    $code = '';
                                    $cl1z = 0;
                                    $cl2z = 0;
                                    $cl3z = 0;
                                    $cl4z = 0;
                                    $cl5z = 0;
                                    $cl6z = 0;
                                    $cl7z = 0;
                                    $cl8z = 0;
                                    $cl9z = 0;
                                    $cl1v = 0;
                                    $cl2v = 0;
                                    $cl3v = 0;
                                    $cl4v = 0;
                                    $cl5v = 0;
                                    $cl6v = 0;
                                    $cl7v = 0;
                                    $cl8v = 0;
                                    $cl9v = 0;
                                    $cl10v = 0;
                                    $cl11v = 0;
					                $designation = ' ';
                                    $workTitle = ' ';
                                    $toidn = 0;
                                    $toid = ' ';

                                    $j++;
                                    foreach ($cellIterator as $cell)
                                    {
                                      if(!is_null($cell))
                                      {
                                          $i++;

                                          if($j == 1)
                                              break 1;
                                          if($i == 1) $code = $cell->getValue();// Code
                                          if($i == 2) $workTime =  $cell->getValue(); // WorkTime
                                          if($i == 3) $materialPrice =  $cell->getValue(); // MaterialPrice
                                          if($i == 4) $quarter =  $cell->getValue(); // Quarter
                                          if($i == 5) $year =  $cell->getValue(); // Year
                                          if($i == 6) $priority =  $cell->getValue(); // Priority
                                          if($i == 7) $edAreaCode =  $cell->getValue(); // EDAreaCode
                                          if($i == 8) $worker =  $cell->getValue(); // Darbuzņēmējs
                                          if($i == 9) $contract =  $cell->getValue(); // Līgums
                                          if($i == 10) $trase =  $cell->getValue(); // DU trases
                                          if($i == 11) $cl1z = $cell->getValue();// Fiz. radītājs
                                          if($i == 12) $cl2z = $cell->getValue();// Fiz. radītājs
                                          if($i == 13) $cl3z = $cell->getValue();// Fiz. radītājs
                                          if($i == 14) $cl4z = $cell->getValue();// Fiz. radītājs
                                          if($i == 15) $cl5z = $cell->getValue();// Fiz. radītājs
                                          if($i == 16) $cl6z = $cell->getValue();// Fiz. radītājs
                                          if($i == 17) $cl7z = $cell->getValue();// Fiz. radītājs
                                          if($i == 18) $cl8z = $cell->getValue();// Fiz. radītājs
                                          if($i == 19) $cl9z = $cell->getValue();// Fiz. radītājs
                                          if($i == 20) $cl1v = $cell->getValue();// Fiz. radītājs
                                          if($i == 21) $cl2v = $cell->getValue();// Fiz. radītājs
                                          if($i == 22) $cl3v = $cell->getValue();// Fiz. radītājs
                                          if($i == 23) $cl4v = $cell->getValue();// Fiz. radītājs
                                          if($i == 24) $cl5v = $cell->getValue();// Fiz. radītājs
                                          if($i == 25) $cl6v = $cell->getValue();// Fiz. radītājs
                                          if($i == 26) $cl7v = $cell->getValue();// Fiz. radītājs
                                          if($i == 27) $cl8v = $cell->getValue();// Fiz. radītājs
                                          if($i == 28) $cl9v = $cell->getValue();// Fiz. radītājs
                                          if($i == 29) $cl10v = $cell->getValue();// Fiz. radītājs
                                          if($i == 30) $cl11v = $cell->getValue();// Fiz. radītājs
						                  if($i == 31) $designation = $cell->getValue();// Operativais apzim橵ms
                                          if($i == 32) $workTitle = $cell->getValue();// Darba nosaukums
                                          if($i == 33) $toidn = $cell->getValue();// TO_IDN
                                          if($i == 34) $toid = $cell->getValue();// TO_ID

                                      }
                                    }
                                    // save material record
                                    if($j > 1)
                                    {
                                      if($code != '')
                                      {
                                        $r2=dbProc::replaceMMSWork($code,
                                            number_format($workTime, 2, '.', ''),
                                            number_format($materialPrice, 2, '.', ''),
                                            $quarter, $year,$priority,$edAreaCode, 0,$worker, $contract, $trase, true,
                                            $cl1z, $cl2z, $cl3z, $cl4z, $cl5z, $cl6z, $cl7z, $cl8z, $cl9z,
                                            $cl1v, $cl2v, $cl3v, $cl4v, $cl5v, $cl6v, $cl7v, $cl8v, $cl9v, $cl10v, $cl11v, $designation, $workTitle, $toidn, $toid);
                                        if($r2 === false )
                                        {
                                            files::eraseFileFromStore2($file);
                                            break 2;
                                        }
                                      }
                                    }
                                  }
                               break;
                            // catalog Materials
                            case 'MATERIAL':

                                /*$r = dbProc::createMaterialTempTable();
                                if($r === false)
                                {
                                  dbProc::deleteMaterialTable(false);
                                  files::eraseFileFromStore2($file);
                                }

                                $j = 0;
                                foreach ($objWorksheet->getRowIterator() as $row)
                                {
                                    $cellIterator = $row->getCellIterator();
                                    $cellIterator->setIterateOnlyExistingCells(true);

                                    $i = 0;
                                    $code = '';
                                    foreach ($cellIterator as $cell)
                                    {
                                      if(!is_null($cell))
                                      {
                                          $i++;
                                          $j++;
                                          if($j == 1)
                                              break 1;
                                          if($i == 1)  $code = $cell->getValue();// Code
                                          if($i == 2) $title =  $cell->getValue(); // Title
                                          if($i == 3) $measure =  $cell->getValue(); // Miasure
                                          if($i == 4) $amount =  $cell->getValue(); // Amount
                                          if($i == 5) $price =  $cell->getValue(); // Price

                                      }
                                    }    //echo $code.'-'.$title.'-'.$price.'-'.$amount.'-'.$measure.'-'.$stand."<br>";
                                    // save material record
                                    if($j > 1)
                                    {
                                      if($code != '')
                                      {
                                        $r2=dbProc::saveMaterial(false, $code, $title,
                                            number_format($price, 2, '.', ''),
                                            number_format($amount, 2, '.', ''),
                                            $measure, 1, false);
                                        if($r2 === false )
                                        {
                                            dbProc::deleteMaterialTable(false);
                                            files::eraseFileFromStore2($file);
                                            break 2;
                                        }
                                      }
                                    }
                                  }
                                  // ja visi ieraksti veiksmigi importēti, tad jaizdzest veco personāls tabulu un japarsauc jaunizveidotu
                                  if($r2)
                                  {
                                      $r3 = dbProc::deleteMaterialTable();

                                      $r4 = dbProc::renameMaterialTable();
                                  }
                                  if($r === false || $r2 === false || $r3 === false || $r4 === false)
                                  {
                                      dbProc::deleteMaterialTable(false);
                                  }*/
                               /* $r = true;
                                $r3 = true;
                                $r4 = true;

                                $j = 0;
                                foreach ($objWorksheet->getRowIterator() as $row)
                                {
                                    $cellIterator = $row->getCellIterator();
                                    $cellIterator->setIterateOnlyExistingCells(true);

                                    $i = 0;
                                    $code = '';
                                    foreach ($cellIterator as $cell)
                                    {
                                      if(!is_null($cell))
                                      {
                                          $i++;
                                          $j++;
                                          if($j == 1)
                                              break 1;
                                          if($i == 1)  $code = $cell->getValue();// Code
                                          if($i == 2) $title =  $cell->getValue(); // Title
                                          if($i == 3) $measure =  $cell->getValue(); // Miasure
                                          if($i == 4) $price =  $cell->getValue(); // Price

                                      }
                                    }
                                    // save material record
                                    if($j > 1)
                                    {
                                      if($code != '')
                                      {
                                        $r2=dbProc::replaceMaterial($code, $title,
                                            number_format($price, 2, '.', ''),
                                            $measure, 1);
                                        if($r2 === false )
                                        {
                                            files::eraseFileFromStore2($file);
                                            break 2;
                                        }
                                      }
                                    }
                                  }
                                break;
                         }
                         files::eraseFileFromStore2($file);
                    }
                    // if operation was compleated succefully, show success mesage and redirect current frame
                    if($r !== false && $r2 !== false && $r3 !== false && $r4 !== false)
                    {
                      if($oForm -> getValue('catalog') == 'MMS_WORKS'  OR $oForm -> getValue('catalog') == 'KALKULATION_STATUSS' )
                      {
                        $oLink=new urlQuery();
    	                $oLink->addPrm('isNew', '1');
    	                $oLink->addPrm(FORM_ID, 'f.ktl.s.13');
    					$oLink->addPrm('successMessage', text::get('IMPORT_SUCCESS'));
    					RequestHandler::makeRedirect($oLink->getQuery());
                      }
                      else
                      {
                        // list
                    	$oLink=new urlQuery();
                    	$oLink->addPrm('isNew', '1');
                        switch (  $oForm -> getValue('catalog'))
                         {
                            // catalog Customers
                            case 'EDAREA':
                    	        $oLink->addPrm(FORM_ID, 'f.ktl.s.5');
                                break;

                            // catalog Materiali
                            case 'MATERIAL':
                    	        $oLink->addPrm(FORM_ID, 'f.ktl.s.1');
                                break;
                            // catalog Kalulācija
                            case 'KALKULATION':
                    	        $oLink->addPrm(FORM_ID, 'f.ktl.s.10');
                                break;
                            // catalog trase Kalulācija
                            case 'KALKULATION_TR':
                                $oLink->addPrm('isTrase', '1');
                    	        $oLink->addPrm(FORM_ID, 'f.ktl.s.10');
                                break;
	             // catalog saskaņotāji
                            case 'HARMONIZED':
                                $oLink->addPrm(FORM_ID, 'f.ktl.s.4');
                                break;
                         }
                    	$listLink=$oLink ->getQuery();
                    	unset($oLink);
                    	// add/edit
                    	$oLink=new urlQuery();
                        switch (  $oForm -> getValue('catalog'))
                         {
                            // catalog Customers
                            case 'EDAREA':
                    	        $oLink->addPrm(FORM_ID, 'f.ktl.s.5');
                                break;

                            // catalog Material
                            case 'MATERIAL':
                    	        $oLink->addPrm(FORM_ID, 'f.ktl.s.1');
                                break;
                            // catalog Kalulācija
                            case 'KALKULATION':
                    	        $oLink->addPrm(FORM_ID, 'f.ktl.s.10');
                                break;
                            // catalog trase Kalulācija
                            case 'KALKULATION_TR':
                                $oLink->addPrm('isTrase', '1');
                    	        $oLink->addPrm(FORM_ID, 'f.ktl.s.10');
                                break;
                            // catalog saskaņotāji
                            case 'HARMONIZED':
                                $oLink->addPrm(FORM_ID, 'f.ktl.s.4');
                                break;
                         }
                    	$oLink->addPrm('editMode', '1');
                    	$editLink = $oLink->getQuery();
                    	unset($oLink);

    		            $oForm->addElement('static','jsRefresh2','','
                        <script>
                            parent["frameTop"].enableFrameControl();
                            window.top.enableResize();
                            window.top.normal();
                            reloadFrame(1,"'.$listLink.'");
                            reloadFrame(2,"'.$editLink.'");
                            reloadFrame(3,"");
                       </script>
                       ');
                       }
                    }
                    else
                    {
                       files::eraseFileFromStore2($file);
                       $oForm->addError(text::get('ERROR_IMPORT_NOT_SUCCESS'));
                    }
           		}*/
                else
        	    {
        		    $oForm->addError(text::get('ERROR_NOT_CORRECT_TYPE_OF_FILE'));
        	    }
    		}
            else
    	    {
    		    $oForm->addError(text::get('ERROR_NO_ALL_INPUT_DATES'));
    	    }
    	}

    }
    $oForm -> makeHtml();
    include('f.ktl.s.13.tpl');
}
else
{
	RequestHandler::showErrorAndDie(text::get('ERROR_NOT_PERMISSION'));
}
?>