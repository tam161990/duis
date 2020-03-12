<?
   $sCriteria = reqVar::get('search');
   $sOrder = reqVar::get('sortOrder');
   // TRASE act
   $trase =  reqVar::get('isTrase');
   $searchCr = array();
        $sCr = explode("^", $sCriteria);
        if(isset($sCr[0]) && $sCr[0] != -1  )
        {
           $searchCr[] = text::get('YEAR').': '.$sCr[0];
        }
        if(isset($sCr[1]) && $sCr[1] != -1  && isset($sCr[2]) && $sCr[2] != -1)
        {
           $searchCr[] = text::get('MONTH').': '.dtime::getMonthName($sCr[1]).' - '.dtime::getMonthName($sCr[2]);
        }
        if(isset($sCr[3]) && $sCr[3] != -1)
        {
           $searchCr[] = text::get('SINGL_WORK_OWNER').': '.dbProc::getWorkOwnerNameByCode($sCr[3]);
        }
        if(isset($sCr[4]) && $sCr[4] != -1)
        {
           $searchCr[] = text::get('ED_REGION').': '.$sCr[4];
        }
        if(isset($sCr[5]) && $sCr[5] != -1)
        {
           $searchCr[] = text::get('SINGLE_VOLTAGE').': '.dbProc::getVoltageName($sCr[5]);
        }

        if(isset($sCr[6]) && $sCr[6] != -1)
        {
           $searchCr[] = text::get('SINGLE_ACT_TYPE').': '.dbProc::getActTypeName($sCr[6]);
        }

        $status = explode("*", $sCr[8]);
        $statusString = '';
        if($status[0] == -1)
        {
           $statusString = text::get('ALL_STATUS');
        }
        else
        {
          foreach($status as $s)
          {
              $statusInfo = dbProc::getKrfkInfoByName($s);
              $statusString .= $statusInfo['KRFK_NOZIME'].",";
          }
          $statusString  = substr($statusString, 0, -1);
        }
        $searchCr[] = text::get('STATUS').': '.$statusString;
        if(isset($sCr[9]) && $sCr[9] != -1)
        {
           $searchCr[] = text::get('ED_SECTION').': '.$sCr[9];
        }
   $excel = '<html><head><meta http-equiv=Content-Type content="text/html; charset=utf-8"></head><body>';

   $excel .= '<table style="font-family:Arial; font-size:9pt;">';

   $excel .= '<tr><td colspan="20" style="font-size:12pt; font-weight:bold;">'.text::get('REPORT_MAIN_ACT').(($trase == 1) ? ' ('.text::get('TRASE').')' : '' ).'</td></tr>';
   $excel .= '<tr><td colspan="20">'.implode('; ',$searchCr).'</td></tr>';
   $excel .= '<tr>';
   $excel .= '<td style="border: 1px solid black; font-size:10pt; font-weight:bold; text-align:center">'.text::get('SINGL_WORK_OWNER').'</td>';
   $excel .= '<td style="border: 1px solid black; font-size:10pt; font-weight:bold; text-align:center">'.text::get('ACT_NUMBER').'</td>';
   $excel .= '<td style="border: 1px solid black; font-size:10pt; font-weight:bold; text-align:center">'.text::get('SINGLE_ACT_TYPE').'</td>';
   $excel .= '<td style="border: 1px solid black; font-size:10pt; font-weight:bold; text-align:center">'.text::get('STATUS').'</td>';
   $excel .= '<td style="border: 1px solid black; font-size:10pt; font-weight:bold; text-align:center">'.text::get('DATE').'</td>';
   $excel .= '<td style="border: 1px solid black; font-size:10pt; font-weight:bold; text-align:center">'.text::get('SINGLE_VOLTAGE').'</td>';
   $excel .= '<td style="border: 1px solid black; font-size:10pt; font-weight:bold; text-align:center">'.text::get('SINGLE_OBJECT').'</td>';
   $excel .= '<td style="border: 1px solid black; font-size:10pt; font-weight:bold; text-align:center">'.text::get('MAIN_DESIGNATION').'</td>';

   $excel .= '<td style="border: 1px solid black; font-size:10pt; font-weight:bold; text-align:center">'.text::get('ACT_TOTAL_WORK_PRICE').'</td>';
   $excel .= '<td style="border: 1px solid black; font-size:10pt; font-weight:bold; text-align:center">'.text::get('ST_TOTAL_MATER_PRICE').'</td>';
   $excel .= '<td style="border: 1px solid black; font-size:10pt; font-weight:bold; text-align:center">'.text::get('ACT_TOTAL_MATER_PRICE').'</td>';

   $excel .= '<td style="border: 1px solid black; font-size:10pt; font-weight:bold; text-align:center">'.text::get('COMMENT').'</td>';

   $excel .= '<td style="border: 1px solid black; font-size:10pt; font-weight:bold; text-align:center">'.text::get('ED_REGION').'</td>';

   $excel .= '<td style="border: 1px solid black; font-size:10pt; font-weight:bold; text-align:center">'.text::get('ED_SECTION').'</td>';
   $excel .= '<td style="border: 1px solid black; font-size:10pt; font-weight:bold; text-align:center">'.text::get('IN_AAUD_DATUMS').'</td>';
   $excel .= '<td style="border: 1px solid black; font-size:10pt; font-weight:bold; text-align:center">'.text::get('AC_AAUD_DATUMS').'</td>';
    $excel .= '<td style="border: 1px solid black; font-size:10pt; font-weight:bold; text-align:center">'.text::get('CL_AAUD_DATUMS').'</td>';
    $excel .= '<td style="border: 1px solid black; font-size:10pt; font-weight:bold; text-align:center">'.text::get('WO_AAUD_DATUMS').'</td>';
   $excel .= '</tr>';
        $res = dbProc::getActFullList($sCriteria, $sOrder, $trase);
        $work = 0;
        $st_material = 0;
        $du_material = 0;
        $currentRow = 4;
        if (is_array($res))
		{
			foreach ($res as $i=>$row)
			{
			  $excel .= '<tr>';
              $excel .= '<td style="border: 1px solid black;">'.$row['WORKER'].'</td>';
              $excel .= '<td style="border: 1px solid black;">'.sprintf(" %s",$row['NUMURS']).'</td>';
              $excel .= '<td style="border: 1px solid black;">'.$row['TYPE'].'</td>';
              $excel .= '<td style="border: 1px solid black;">'.$row['STATUS_NAME'].'</td>';
              $excel .= '<td style="border: 1px solid black;">'.$row['AAUD_DATUMS'].'</td>';
              $excel .= '<td style="border: 1px solid black;">'.$row['KSRG_NOSAUKUMS'].'</td>';

              $excel .= '<td style="border: 1px solid black;">'.$row['KOBJ_NOSAUKUMS'].'</td>';
              $excel .= '<td style="border: 1px solid black;">'.$row['RAKT_OPERATIVAS_APZIM'].'</td>';


              $excel .= '<td style="border: 1px solid black;">'.number_format($row['WORK_TOTAL'],2,'.','').'</td>';
              $excel .= '<td style="border: 1px solid black;">'.number_format($row['ST_MATER_TOTAL'],2,'.','').'</td>';
              $excel .= '<td style="border: 1px solid black;">'.number_format($row['DU_MATER_TOTAL'],2,'.','').'</td>';

              $excel .= '<td style="border: 1px solid black;">'.$row['RAKT_PIEZIMES'].'</td>';

              $excel .= '<td style="border: 1px solid black;">'.$row['KEDI_REGIONS'].'</td>';
              $excel .= '<td style="border: 1px solid black;">'.$row['KEDI_SECTION'].'</td>';
              $excel .= '<td style="border: 1px solid black;">'.$row['IN_AAUD_DATUMS'].'</td>';
              $excel .= '<td style="border: 1px solid black;">'.$row['AC_AAUD_DATUMS'].'</td>';
              $excel .= '<td style="border: 1px solid black;">'.$row['CL_AAUD_DATUMS'].'</td>';
              $excel .= '<td style="border: 1px solid black;">'.$row['WO_AAUD_DATUMS'].'</td>';
              $excel .= '</tr>';
               $work = $work + $row['WORK_TOTAL'];
               $st_material = $st_material + $row['ST_MATER_TOTAL'];
               $du_material = $du_material + $row['DU_MATER_TOTAL'];
               $currentRow ++;
			}
		}

        $excel .= '<tr>';
        $excel .= '<td colspan="8" style="font-weight:bold; text-align:right; font-style: italic">'.text::get('TOTAL').':'.'</td>';
        $excel .= '<td style="font-weight:bold; font-style: italic">'.number_format($work, 2, '.', '').'</td>';
        $excel .= '<td style="font-weight:bold; font-style: italic">'.number_format($st_material, 2, '.', '').'</td>';
        $excel .= '<td style="font-weight:bold; font-style: italic">'.number_format($du_material, 2, '.', '').'</td>';
        $excel .= '</tr>';
        $excel .= '</table></body></html>';

// redirect output to client browser

  header('Content-Type: application/vnd.ms-excel;');
  header('Content-Disposition: attachment;filename="myfile.xls"');
  header('Cache-Control: max-age=0');

  echo $excel;


?>