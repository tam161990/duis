<?
// Created by Tatjana Fedorkova
$userId = userAuthorization::getUserId();
$isAdmin=userAuthorization::isAdmin();
$isProjector = dbProc::isExistsUserRoleWithProject($userId) ;
$projectApprover = dbProc::isUserInRole($userId, ROLE_PROJ_APPROVER);
// act ID
$actId  = reqVar::get('actId');


// tikai  sistēmas lietotajam vai administrātoram ir pieeja!
if ( $isAdmin || $isProjector ||  $projectApprover)
{
    if($actId !== false )
    {

      // get grupas list
      $workType=array();
      $res=dbProc::getWorkTypeListByWork($actId);
      if (is_array($res))
      {
        foreach ($res as $row)
        {
          $workType[$row['KLDV_ID'].'^'.(isset($row['DRBI_WORK_TYPE_TEXT']) ? str_replace('"', '\'', $row['DRBI_WORK_TYPE_TEXT']) : 'X')] =$row['KLDV_NOSAUKUMS'].' '.$row['DRBI_WORK_TYPE_TEXT'];
        }
      }
      unset($res);

      $aMaterials = array();
      $aMaterialExist = false;
      $sortOrder = false;
      $orderColumn = false;

      //Ja eksistee akta materiāli, tad nolasaam taas darbus no datu baazes
      $aMaterialDb=dbProc::getActMaterialList($actId, false, false, true,  $sortOrder, $orderColumn);

      foreach ($aMaterialDb as $material)
      {
        $material['MATR_PIEZIMES'] = ($material['MATR_PIEZIMES'] == 'NULL') ? '' : $material['MATR_PIEZIMES'];
        $aMaterials[$material['MATR_WORK_TYPE']][] = $material;   
          
        $aMaterialExist = true;     
      }

      if(!$aMaterialExist) {
        $aMaterials[0] = array();          
      } 
      include('f.akt.s.25.tpl');
    }
}
else
{
    RequestHandler::showErrorAndDie(text::get('ERROR_NOT_PERMISSION'));
}

?>