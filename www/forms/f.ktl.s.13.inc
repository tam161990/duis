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
          if (userAuthorization::isSuperAdmin() ) {
            if($row['nosaukums'] == 'ACT_DELETE') {
              $catalog[$row['nosaukums']]=$row['nozime'];
            }
          }
          if ($isEdUser ) {
            if ($row['nosaukums'] == 'MMS_WORKS' ||  $row['nosaukums'] == 'KALKULATION') {
              $catalog[$row['nosaukums']]=$row['nozime'];
            }
          }
          if (userAuthorization::isAdmin() ) {           
              if($row['nosaukums'] != 'ACT_DELETE') {
                $catalog[$row['nosaukums']]=$row['nozime'];
              }            
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
      $oForm -> addElement('submitImg', 'submit', text::get('DO_IMPORT'), 'img/btn_import.gif', 'width="70" height="20" onClick="setPosition1(\'loading\'); return true;" '.((!userAuthorization::isAdmin() && $isEdUser)?' disabled' : ''));
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
                      
                     // if($oForm -> getValue('catalog') == 'MMS_WORKS')
                     // {
                     //     $mms_exists = dbProc::is_mms_exists();
                     // }           
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
                                  $r2 = dbProc::saveMmsFromCsv($data, $userId);                                     
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
                                // catalog sDU lietotāju
                                case 'DUUSERS':
                                  $r2 = dbProc::saveUserFromCsv($data, $userId);
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
                        $r2 = dbProc::processAutoActs($userId);
                      }
                  }
              }
              // calculation
              elseif(files::isUploadFileOfTYpe('fileName', 'application/vnd.ms-excel'))
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
                          // catalog Kalkulacija
                          case 'KALKULATION':                           
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
                                    $j++;
                                    if($j == 1)
                                        break 1;
                                    $data[$i] =  $cell->getValue();
                                    $i++;                                      
                                  }
                              }
                              // save kalkulācijas record
                              if($j > 1)
                              {
                                $r2 = dbProc::saveCalculationFromCsv($data, $userId);
                                
                              }
                            }                            
                            break;
                            // DU lietotāji
                            case 'DUUSERS':                           
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
                                      $j++;
                                      if($j == 1)
                                          break 1;
                                      $data[$i] =  $cell->getValue();
                                      $i++;                                      
                                    }
                                }
                                // save kalkulācijas record
                                if($j > 1)
                                {
                                  $r2 = dbProc::saveUserFromCsv($data, $userId);
                                  
                                }
                              }                            
                              break;
                            // materiālu kategorijas
                            case 'MATERIAL_CATEGORY':                           
                            $j = 0;
                            $r = dbProc::createMaterialGroupTempTable();
                            if($r !== false) {
                              foreach ($objWorksheet->getRowIterator() as $row)
                              {
                                  $cellIterator = $row->getCellIterator();
                                  $cellIterator->setIterateOnlyExistingCells(false);
    
                                  $i = 0;    
                                  foreach ($cellIterator as $cell)
                                  {
                                      $j++;
                                      if($j == 1)
                                          break 1;
                                      $data[$i] =  $cell->getValue();
                                      $i++;    
                                  }
                                  // save matr kategorijas record
                                  if($j > 1)
                                  {
                                    $r2 = dbProc::saveMaterialKategoryFromExcel($data);
                                    
                                  }
                                }  
                                $r =  dbProc::renameMaterialGroupTable();     
                            }                    
                            break;
                            // Materiālu kompkektācija
                            case 'MATERIAL_COMPLECTATION':                           
                              $j = 0;
                              $r = dbProc::createMaterialComplectTempTable();
                              if($r !== false) {
                                foreach ($objWorksheet->getRowIterator() as $row)
                                {
                                    $cellIterator = $row->getCellIterator();
                                    $cellIterator->setIterateOnlyExistingCells(true);
      
                                    $i = 0;    
                                    foreach ($cellIterator as $cell)
                                    {
                                      if(!is_null($cell))
                                      {                                      
                                          $j++;
                                          if($j == 1)
                                              break 1;
                                          $data[$i] =  $cell->getValue();
                                          $i++;                                      
                                        }
                                    }
                                    // save kalkulācijas record
                                    if($j > 1)
                                    {
                                      $r2 = dbProc::saveMaterialComplectFromExcel($data);
                                      
                                    }
                                  }
                                  $r =  dbProc::renameMaterialComplectTable();                             
                                }
                                break;
                            // Materiālu kompkektācija
                            case 'COMPLECTATION':                           
                              $j = 0;
                              $r = dbProc::createComplectTempTable();
                              if($r !== false) {
                                foreach ($objWorksheet->getRowIterator() as $row)
                                {
                                    $cellIterator = $row->getCellIterator();
                                    $cellIterator->setIterateOnlyExistingCells(true);
      
                                    $i = 0;    
                                    foreach ($cellIterator as $cell)
                                    {
                                      if(!is_null($cell))
                                      {                                      
                                          $j++;
                                          if($j == 1)
                                              break 1;
                                          $data[$i] =  $cell->getValue();
                                          $i++;                                      
                                        }
                                    }
                                    // save kalkulācijas record
                                    if($j > 1)
                                    {
                                      $r2 = dbProc::saveComplectationFromExcel($data);
                                      
                                    }
                                  }
                                  $r =  dbProc::renameComplectTable();                             
                                }
                                break;
                          // akta dzēšana
                          case 'ACT_DELETE':
                            if (userAuthorization::isSuperAdmin() )
                            {
                              $j = 0;
                              foreach ($objWorksheet->getRowIterator() as $row)
                              {
                                  $cellIterator = $row->getCellIterator();
                                  $cellIterator->setIterateOnlyExistingCells(true);
                                  
                                  $i = 0;    
                                  foreach ($cellIterator as $cell)
                                  {
                                    if($i > 1 ) {
                                      $r2 = false;
                                      break 2;
                                    }
                                    if(!is_null($cell))
                                    {                                      
                                        $j++;
                                        if($j == 1)
                                            break 1;
                                        $data[] =  $cell->getValue();
                                        $i++;                                      
                                      }
                                  }                                  
                              }
                              // dzēst visus failus
                              if($j > 1)
                              {
                                $r2 = dbProc::deleteActXLS($data);
                              }                            
                          }
                          break;
                      }
                  }
              } 
              else
        	    {
        		    $oForm->addError(text::get('ERROR_NOT_CORRECT_TYPE_OF_FILE'));
        	    }
            }
        }
        else
    	  {
    		    $oForm->addError(text::get('ERROR_NO_ALL_INPUT_DATES'));
    	  }
        // if operation was compleated succefully, show success mesage and redirect current frame
        if($r !== false && $r2 !== false)
        {
          if($oForm -> getValue('catalog') == 'MMS_WORKS' ||
            $oForm -> getValue('catalog') == 'MATERIAL_CATEGORY' ||
            $oForm -> getValue('catalog') == 'MATERIAL_COMPLECTATION' ||
            $oForm -> getValue('catalog') == 'COMPLECTATION' ||
            $oForm -> getValue('catalog') == 'ACT_DELETE'
          )
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
                // catalog sDU lietotāju
                case 'DUUSERS':      
                  $oLink->addPrm(FORM_ID, 'f.ktl.s.2');
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
                // catalog sDU lietotāju
                 case 'DUUSERS':      
                  $oLink->addPrm(FORM_ID, 'f.ktl.s.2');
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
    $oForm -> makeHtml();
    include('f.ktl.s.13.tpl');
}
else
{
	RequestHandler::showErrorAndDie(text::get('ERROR_NOT_PERMISSION'));
}
?>