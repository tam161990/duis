<?
//created by Tatjana Fedorkova
$userId = userAuthorization::getUserId();
$isAdmin=userAuthorization::isAdmin();
$isSystemUser = dbProc::isExistsUserRole($userId);
// TRASE act
   $trase =  reqVar::get('isTrase');
   $sign =  reqVar::get('sign');
// tikai  sistēmas lietotajam vai administrātoram ir pieeja!
if(true/*$isEdUser || $isAdmin*/)
{
	$searchMode = reqVar::get('isSearch');
	// top frame
    if($searchMode)
	{
        $oLink=new urlQuery();
    	  $oLink->addPrm(FORM_ID, 'f.rpt.s.3');
    	  $oLink->addPrm('isSearch', 1 );
        $oLink->addPrm('isTrase', $trase );
        $oLink->addPrm('sign', $sign );
    	  // form inicialization
    	  $oForm = new Form('frmMain','post',$oLink->getQuery());
    	  unset($oLink);

        $oLink=new urlQuery();
	      $oLink->addPrm('isReturn', '1');
        $oLink->addPrm('isSearch', 1 );
        $oLink->addPrm('isTrase', $trase );
        $oLink->addPrm('sign', $sign );
	      $oLink->addPrm(FORM_ID, 'f.rpt.s.3');
	      $criteriaLink=$oLink ->getQuery();
	      unset($oLink);

        // if operation
    	if ($oForm -> isFormSubmitted())
    	{
            $oListLink=new urlQuery();
            $oListLink->addPrm(FORM_ID, 'f.rpt.s.3');
            $oListLink->addPrm('isTrase', $trase );
            $oListLink->addPrm('sign', $sign );
        }
        $searchTitle = text::toUpper(text::toUpper(text::get('REPORT_MATERIAL_TOTAL').(($trase == 1) ? ' ('.text::get('TRASE').')' : '' )));
        $searchName = 'REPORT_MATERIAL_TOTAL';
        include('f.akt.m.4.inc');
	}
	// bottom frale
	else
	{
	    $sCriteria = reqVar::get('search');
        $year = '';
         $month = '';

         $searchCr = array();
         $sCr = explode("^", $sCriteria);
        if(isset($sCr[0]) && $sCr[0] != -1 )
        {
           $year = $sCr[0];
        }
        if(isset($sCr[1]) && $sCr[1] != -1 )
        {
          $month = $sCr[1];
        }
        //if(date("d.m.Y", strtotime("01.".$month.".".$year) ) >= date("d.m.Y", strtotime("01.07.2012") ) )
        if(strtotime("01.".$month.".".$year)  >= strtotime("01.07.2012")  )    
            $pvn = PCT_21  ;
        else
            $pvn = PCT_22  ;

        // URL  export
    	  $oLink = new urlQuery;
    	  $oLink -> addPrm(FORM_ID, 'f.rpt.e.3');
    	  $oLink->addPrm('search', $sCriteria);
        $oLink->addPrm('isTrase', $trase );
        $oLink->addPrm('sign', $sign );
        $oLink->addPrm(DONT_USE_GLB_TPL, '1');
        $exportUrl =  $oLink ->getQuery();
        unset($oLink);

        // gel list of users
		$res = dbProc::getActTotalMaterialList($sCriteria, $trase, $sign);
       /* echo "<pre>";
        print_r($res);
        echo "</pre>";*/

        $area = array();

        $summa = 0;
        $pct = 0;
        $totalMaterialPrice = 0;

        $Totalsumma = 0;
        $Totalpct = 0;
        $Totaltotal = 0;
        if (is_array($res))
		{
            foreach ($res as $i=>$row)
			{
              if($row['MATR_IS_WORKER'] == '0')
              {
                if($row['CENA_KOPA'] == '')
                {
                  $totalMaterialPrice =  $row['MATR_DAUDZUMS'] * $row['MATR_CENA'];
                }
                else
                {
                  $totalMaterialPrice = $row['CENA_KOPA'];
                }
              }
              else
              {
                $totalMaterialPrice = 0;
              }

               $pct =  ($totalMaterialPrice*(100+ $pvn )/ 100 ) - $totalMaterialPrice;
               $summa = ($totalMaterialPrice*(100+ $pvn )/ 100 );

               $area[$row['WRITE_OFF_ACCOUNT']]  = array (
                'writeoftitle' => $row['WRITE_OFF_ACCOUNT'],
                'Cena' => (isset($area[$row['WRITE_OFF_ACCOUNT']]['Cena'])?$area[$row['WRITE_OFF_ACCOUNT']]['Cena']:0) + $totalMaterialPrice,
                'Pct' => (isset($area[$row['WRITE_OFF_ACCOUNT']]['Pct'])?$area[$row['WRITE_OFF_ACCOUNT']]['Pct']:0) + $pct,
                'Total' => (isset($area[$row['WRITE_OFF_ACCOUNT']]['Total'])?$area[$row['WRITE_OFF_ACCOUNT']]['Total']:0) + $summa,

                'material' => array()

               );

               $Totalsumma += $totalMaterialPrice;
               $Totalpct += $pct;
               $Totaltotal += $summa;

            }
            $subtitle = '';
             $j = 0;
             $y = 0;
             $writeof = '';
             $code = '';
            foreach ($res as $i=>$row)
	     {
			  //if( $y == 0)   $writeof = $row['WRITE_OFF_ID'];
              /*echo 'subtitle'.$subtitle;
              echo 'MATR_IS_WORKER'.$row['MATR_IS_WORKER'];
              echo 'j'.$j;
              echo 'writeof'.$writeof;
              echo 'WRITE_OFF_ID'.$row['WRITE_OFF_ID'];
              echo "<br>";*/
		/*
	       if($subtitle == '' && $row['MATR_IS_WORKER']  == 1 && ($j == 0 || $writeof != $row['WRITE_OFF_ACCOUNT']))
              {
                 $subtitle = text::get('ST_COMPANY_NAME').' '.text::get('MATERIALS');
                 $j++;
                 $y++;
              }
              elseif($subtitle == '' && $row['MATR_IS_WORKER']  == 0 && ($j == 1  || ($y == 0 && $writeof != $row['WRITE_OFF_ACCOUNT'])))
              {
                  $subtitle = $row['WORKER'].' '.text::get('MATERIALS');
                  $j = 0;
                  $y = 0;
              }
		*/
		if($row['MATR_IS_WORKER']  == 1 && ($j == 0 || $writeof != $row['WRITE_OFF_ACCOUNT']))
              {
                 $subtitle = text::get('ST_COMPANY_NAME').' '.text::get('MATERIALS');
                 $j++;
                 
              }
              elseif($row['MATR_IS_WORKER']  == 0 && ($j > 0  || ($y == 0 && $writeof != $row['WRITE_OFF_ACCOUNT'])))
              {
                  $subtitle = $row['WORKER'].' '.text::get('MATERIALS');
                  $j = 0;
                  $y ++;
              }

              if($row['CENA_KOPA'] == '')
              {
                $totalMaterialPrice =  $row['MATR_DAUDZUMS'] * $row['MATR_CENA'];
              }
              else
              {
                $totalMaterialPrice = $row['CENA_KOPA'];
              }

              $writeof = $row['WRITE_OFF_ACCOUNT'];
             
              //$code =  isset($row['MATR_KODS']) ? $row['MATR_KODS'] : $row['MATR_ID'];
		$code =  $row['MATR_ID'];

              $area[$row['WRITE_OFF_ACCOUNT']]['material'][$code]  = array (
                  'worker' => $row['MATR_IS_WORKER'],
                  'code' => $row['MATR_KODS'],
                  'name' => $row['MATR_NOSAUKUMS'],
                  'miasure' => $row['MATR_MERVIENIBA'],
                  'quantity' => (isset($area[$row['WRITE_OFF_ACCOUNT']]['material'][$code]['quantity'])?$area[$row['WRITE_OFF_ACCOUNT']]['material'][$code]['quantity'] + $row['DAUDZUMS'] :$row['DAUDZUMS']),
                  'cena' => (($row['MATR_IS_WORKER'] == '1')? '0.00' : $row['MATR_CENA']),
                  'total' => (($row['MATR_IS_WORKER'] == '1')? '0.00' : (isset($area[$row['WRITE_OFF_ACCOUNT']]['material'][$code]['total'])?$area[$row['WRITE_OFF_ACCOUNT']]['material'][$code]['total'] + number_format($totalMaterialPrice,2,'.','') :number_format($totalMaterialPrice,2,'.',''))),
                  'subtitle' => $subtitle
                 );
                 $subtitle = '';
            	}
            	
// (isset($area[$row['WRITE_OFF_ACCOUNT']]['material'][$code])?$area[$row['WRITE_OFF_ACCOUNT']]['material'][$code]['subtitle']:$subtitle)

		}
       /*echo "<pre>";
        print_r($area);
        echo "</pre>";*/

		include('f.rpt.s.3.tpl');
	}
}
else
{
	RequestHandler::showErrorAndDie(text::get('ERROR_NOT_PERMISSION'));
}
?>
