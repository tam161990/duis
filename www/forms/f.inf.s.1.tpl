<body class="head" onscroll="this.scrollTo(0,0);return false" >
<script language="JavaScript">
function subMenu(subMenuName,tdName)
{

	var a=getElement(subMenuName,true); 
	var b=getElement(tdName,true);

	if (a.style.visibility=='visible')
	{
		a.style.visibility='hidden';
		b.className='menu_cell_top';
	} 
	else 
	{
		hideMenu();
		a.style.visibility='visible';
		b.className='menu_cell_a';
	}
}

function hideMenu()
{

	var c=getElement('catalogSubMenuDiv',true); c.style.visibility="hidden";
	var c=getElement('tdCatalog',true); c.className="menu_cell_top";
	var c=getElement('actSubMenuDiv',true); c.style.visibility="hidden";
	var c=getElement('tdAct',true); c.className="menu_cell_top";
	var c=getElement('reportSubMenuDiv',true); c.style.visibility="hidden";
	var c=getElement('tdReport',true); c.className="menu_cell_top";
    var c=getElement('optionSubMenuDiv',true); c.style.visibility="hidden";
	var c=getElement('tdOptions',true); c.className="menu_cell_top";
}

function disableFrameControl()
{
	var a=getElement('disabledFrameControl',true);
	a.style.visibility='visible';
	window.top.disableResize();
}

function enableFrameControl()
{
	var a=getElement('disabledFrameControl',true);
	a.style.visibility='hidden';
	window.top.enableResize();
}

</script>

<script type="text/javascript">

if (typeof window.event != 'undefined')
	document.onkeydown = function()
	{
		return (event.keyCode != 8);
	}
else
	document.onkeypress = function(e)
	{
		return (e.keyCode != 8);
	}

</script>



<div id="catalogSubMenuDiv"  class="sub_menu" style="position: absolute;left: 33px;top: 26px;visibility:hidden; z-index:5; ">
<?
if($isAdmin || $isEdUser || $isAuditor )
{
  	?>
	<table cellpadding="0" cellspacing="0" border="0">
		<tr>

		   <td class="menu_cell"><a  target="frame_1" href="<?=$materialListLink;?>" onclick="reloadFrame(2,'<?=$editMaterialLink;?>');reloadFrame(3,'');enableFrameControl();window.top.normal();hideMenu();"><?=text::get('MATERIALS');?></a></td>
           <td class="menu_cell"><a  target="frame_1" href="<?=$regionListLink;?>" onclick="reloadFrame(2,'<?=$editRegionLink;?>');reloadFrame(3,'');enableFrameControl();window.top.normal();hideMenu();"><?=text::get('REGIONS');?></a></td> 
           <td class="menu_cell"><a  target="frame_1" href="<?=$edAreaListLink;?>" onclick="reloadFrame(2,'<?=$editEdAreaLink;?>');reloadFrame(3,'');enableFrameControl();window.top.normal();hideMenu();"><?=text::get('ED_AREA');?></a></td>
           <td class="menu_cell"><a  target="frame_1" href="<?=$voltageListLink;?>" onclick="reloadFrame(2,'<?=$editVoltageLink;?>');reloadFrame(3,'');enableFrameControl();window.top.normal();hideMenu();"><?=text::get('VOLTAGE');?></a></td>
           <td class="menu_cell"><a  target="frame_1" href="<?=$objectListLink;?>" onclick="reloadFrame(2,'<?=$editObjectLink;?>');reloadFrame(3,'');enableFrameControl();window.top.normal();hideMenu();"><?=text::get('OBJECTS');?></a></td>
           <td class="menu_cell"><a  target="frame_1" href="<?=$dUListLink;?>" onclick="reloadFrame(2,'<?=$editDULink;?>');reloadFrame(3,'');enableFrameControl();window.top.normal();hideMenu();"><?=text::get('WORK_OUNERS');?></a></td>
           <td class="menu_cell"><a  target="frame_1" href="<?=$calculationGroupListLink;?>" onclick="reloadFrame(2,'<?=$editCalculationGroupLink;?>');reloadFrame(3,'');enableFrameControl();window.top.normal();hideMenu();"><?=text::get('CALCULATION_GROUP');?></a></td>
           <td class="menu_cell"><a  target="frame_1" href="<?=$calculationListLink;?>" onclick="reloadFrame(2,'<?=$editCalculationLink;?>');reloadFrame(3,'');enableFrameControl();window.top.normal();hideMenu();"><?=text::get('CALCULATION');?></a></td>
           <td class="menu_cell"><a  target="frame_1" href="<?=$actTypeListLink;?>" onclick="reloadFrame(2,'<?=$editActTypeLink;?>');reloadFrame(3,'');enableFrameControl();window.top.normal();hideMenu();"><?=text::get('ACT_TYPE');?></a></td>
           <td class="menu_cell"><a  target="frame_1" href="<?=$userListLink;?>" onclick="reloadFrame(2,'<?=$editUserLink;?>');reloadFrame(3,'');enableFrameControl();window.top.normal();hideMenu();"><?=text::get('USERS');?></a></td>
            <td class="menu_cell"><a  target="frame_1" href="<?=$userDUListLink;?>" onclick="reloadFrame(2,'<?=$editDUUserLink;?>');reloadFrame(3,'');enableFrameControl();window.top.normal();hideMenu();"><?=text::get('USERS_DU');?></a></td>
           <td class="menu_cell"><a  target="frame_1" href="<?=$harmonizedListLink;?>" onclick="reloadFrame(2,'<?=$editHarmonizedLink;?>');reloadFrame(3,'');enableFrameControl();window.top.normal();hideMenu();"><?=text::get('HARMONIZED');?></a></td>
		   <td class="menu_cell"><a  target="frame_1" href="<?=$mmsListLink;?>" onclick="reloadFrame(2,'<?=$editMMSLink;?>');reloadFrame(3,'');enableFrameControl();window.top.normal();hideMenu();"><?=text::get('SINGLE_MMS');?></a></td>
		   <td class="menu_cell" ><a  target="frame_1" href="<?=$mmsCalculationListLink;?>" onclick="reloadFrame(2,'<?=$editMmsCalculationLink;?>');reloadFrame(3,'');enableFrameControl();window.top.min(0);window.top.normal();hideMenu();"><?=text::get('MMS_CALCULATION');?></a></td>
		   <td class="menu_cell" ><a  target="frame_1" href="<?=$calculationMaterialListLink;?>" onclick="reloadFrame(2,'<?=$editCalculationMaterialLink;?>');reloadFrame(3,'');enableFrameControl();window.top.min(0);window.top.normal();hideMenu();"><?=text::get('CALCULATION_MATERIAL');?></a></td>
		   <!--td class="menu_cell" ><a  target="frame_1" href="<?=$workTypeListLink;?>" onclick="reloadFrame(2,'<?=$editWorkTypeLink;?>');reloadFrame(3,'');enableFrameControl();window.top.min(0);window.top.normal();hideMenu();"><?=text::get('WORK_TYPES');?></a></td-->
           <?
if(!$isAuditor)
{
?>
           <td class="menu_cell_2" nowrap><a target="frame_1" href="<?=$catalogImportLink;?>" onclick="reloadFrame(23,'');disableFrameControl();window.top.min(1);hideMenu();"><?=text::get('DATA_IMPORT');?></a></td>
<?
}
?>
		</tr>

	</table>
	<?

}
?>
</div>

<div id="optionSubMenuDiv"  class="sub_menu" style="position: absolute;left: 260px;top: 26px;visibility:hidden;">
<?
if($isAdmin)
{
  	?>
	<table cellpadding="0" cellspacing="0" border="0">
		<tr>
           <td class="menu_cell" nowrap><a target="frame_1" href="<?=$warningLink;?>" onclick="reloadFrame(23,'');disableFrameControl();window.top.min(1);hideMenu();"><?=text::get('WARNING');?></a></td>
           <td class="menu_cell_2" nowrap><a target="frame_1" href="<?=$kvikStepLink;?>" onclick="reloadFrame(23,'');disableFrameControl();window.top.min(1);hideMenu();"><?=text::get('ACT_NUMBER_TEMPLATE');?></a></td>
		   <td class="menu_cell_2" ><a  target="frame_1" href="<?=$jobListLink;?>" onclick="reloadFrame(2,'<?=$editJobLink;?>');reloadFrame(3,'');enableFrameControl();window.top.min(0);window.top.normal();hideMenu();"><?=text::get('SYSTEM_PROCESS');?></a></td>	
		</tr>

	</table>
	<?
}
?>
</div>



<div id="actSubMenuDiv"  class="sub_menu" style="position: absolute;left: 100px;top: 26px;visibility:hidden;">
<?
if($isAdmin || $isSystemUser)
{
  ?>
	<table cellpadding="0" cellspacing="0" border="0">
		<tr>
            
			<td class="menu_cell" nowrap><a  target="frame_1" href="<?=$actSearchLink;?>" onclick="reloadFrame(2,'<?=$actListLink;?>');reloadFrame(3,'');enableFrameControl();window.top.normal();hideMenu();"><?=text::get('ADVANCED_SEARCH');?></a></td>
            
            <?
            			
            if($isAdmin || $isEconomist || $isAuditor || $isEditor )
            {
            ?>
            <td class="menu_cell<?= (!$isAdmin && !$isEditor && !$isProjector)? '_2': '';?>" nowrap><a  target="frame_1" href="<?=$actSearchByNumberLink;?>" onclick="reloadFrame(2,'<?=$actListLink;?>');reloadFrame(3,'');enableFrameControl();window.top.normal();hideMenu();"><?=text::get('SEARCH_BY_NUMBER');?></a></td>
            <?
            }
            if((($isAdmin || $isEditor) && $isContractUser ))
            {
                ?>
			    <td class="menu_cell<?= (!$isAdmin && !$isEditor)? '_2': '';?>" nowrap><a target="frame_1" href="<?=$actLink;?>" onclick="reloadFrame(23,'');disableFrameControl();window.top.min(1);hideMenu();"><?=text::get('NEW');?></a></td>
                <?
            }
            if($isAdmin || $isTraseUser )
            {
                ?>
			    <td class="menu_cell<?= (!$isAdmin && !$isTraseUser)? '_2': '';?>" nowrap><a target="frame_1" href="<?=$actTrLink;?>" onclick="reloadFrame(23,'');disableFrameControl();window.top.min(1);hideMenu();"><?=text::get('TRASES');?></a></td>
                <?
			}
			
            ?>
             <?
            if(($isAdmin || $isEconomist))
            {
                ?>
			    <td class="menu_cell_2" nowrap><a  target="frame_1" href="<?=$actSearchWriteoffLink;?>" onclick="reloadFrame(2,'<?=$actWriteoffLink;?>');reloadFrame(3,'');enableFrameControl();window.top.normal();hideMenu();"><?=text::get('WRITE_OFF_ACT');?></a></td>
                <?
            }
            ?>
        </tr>
	</table>
<?
}
?>
</div>

<div id="reportSubMenuDiv"  class="sub_menu" style="position: absolute;left: 377px;top: 26px;visibility:hidden;">

</div>

<table cellpadding="5" cellspacing="0" border="0" width="100%">
	<tr>
		<td class="head_table_top">

			<table cellpadding="3" cellspacing="0" border="0">
				<tr>

                    <td nowrap class="menu_cell_left"><img src="img/0.gif" alt="" width="10" height="1" class="block"></td>
					<td nowrap id="tdCatalog" class="menu_cell_top" <?=($isAdmin || $isEdUser|| $isAuditor)?'':'disabled';?>><?=($isAdmin || $isEdUser|| $isAuditor)?'<a onclick="subMenu(\'catalogSubMenuDiv\',\'tdCatalog\');return false;" href="#">':'';?><?=text::get('CATALOGS');?><?=($isAdmin || $isEdUser|| $isAuditor)?'</a>':'';?></td>


                    <td nowrap id="tdAct" class="menu_cell_top" <?=($isAdmin || $isContractUser || $isTraseUser)?'':'disabled';?>><?=($isAdmin|| $isContractUser || $isTraseUser)?'<a onclick="subMenu(\'actSubMenuDiv\',\'tdAct\');return false;" href="#">':'';?><?=text::get('ACTS');?><?=($isAdmin || $isContractUser || $isTraseUser)?'</a>':'';?></td>
			<td nowrap id="tdReport" class="menu_cell_top" <?=($isAdmin || $isContractUser || $isTraseUser)?'':'disabled';?>><?=($isAdmin || $isContractUser || $isTraseUser)?'<a onclick="reloadFrame(23,\'\');disableFrameControl();window.top.min(1);hideMenu();" href="'.$cRepMain.'" target="frame_1">':'';?><?=text::get('REPORT');?><?=($isAdmin || $isContractUser || $isTraseUser)?'</a>':'';?></td>
                    	<td nowrap id="tdGps" class="menu_cell_top" <?=($isEditor || $isEdUser || $isAdmin)?'':'disabled';?>><?=($isEditor || $isEdUser || $isAdmin)?'<a onclick="reloadFrame(23,\'\');disableFrameControl();window.top.min(1);hideMenu();" href="'.$cGpsMain.'" target="frame_1">':'';?><?=text::get('GPS');?><?=($isEditor || $isEdUser || $isAdmin)?'</a>':'';?></td>
                    <td nowrap id="tdOptions" class="menu_cell_top" <?=($isAdmin)?'':'disabled';?>><?=($isAdmin)?'<a onclick="subMenu(\'optionSubMenuDiv\',\'tdOptions\');return false;" href="#">':'';?><?=text::get('OPTIONS');?><?=($isAdmin)?'</a>':'';?></td>
					<td nowrap class="menu_cell_right">&nbsp;</td>
				</tr>
			</table>
		</td>
       <td class="head_table_top_brown"><?=text::get('USER');?>: <?=$userName;?> <?=$userSurName;?>   </td>
		<td class="head_table_top">
			<table cellpadding="2" cellspacing="0" border="0">
				<tr>
					<td><a target="_top" href="<?=$exitUrl;?>"><img src="img/ico_end.gif" alt="<?=text::get('EXIT');?>" width="15" height="15" border="0" class="block"></a></td>
					<td><a target="_top" href="<?=$exitUrl;?>" class="red"><?=text::get('EXIT');?></a></td>
				</tr>
			</table>
		 </td>
	</tr>
	<tr valign=top>
		<td class="head_table_bot">

		</td>
		<td class="head_table_bot_brown"><table cellpadding="0" cellspacing="0" border="0"><tr><td style="color: #716F60;"></td><td nowrap ><img src="img/0.gif" alt="" width="1" height="20" class="block"></td></tr></table></td>
		<td class="head_table_bot">
			<table cellpadding="2" cellspacing="0" border="0">
				<tr>
					<td><a onclick="window.top.normal();return false;" href="#"><img src="img/ico_layout_1.gif" alt="<?=text::get('NORMAL_VIEW');?>" width="15" height="15" border="0" class="block"></a></td>
					<td><a onclick="window.top.min(1);return false;" href="#"><img src="img/ico_layout_2.gif" alt="<?=text::get('MIN_BOTTOM_VIEW');?>" width="15" height="15" border="0" class="block"></a></td>
					<td><a onclick="window.top.min(2);return false;" href="#"><img src="img/ico_layout_3.gif" alt="<?=text::get('MIN_TOP_VIEW');?>" width="15" height="15" border="0" class="block"></a></td>
				</tr>
			</table>
			<div id="disabledFrameControl"  style="position: relative;left: 0px;top: -19px;visibility:hidden;z-index:4;">
				<table cellpadding="2" cellspacing="0" border="0">
					<tr>
						<td><img src="img/ico_layout_1_disabled.gif" alt="<?=text::get('NORMAL_VIEW');?>" width="15" height="15" border="0" class="block"></td>
						<td><img src="img/ico_layout_2_disabled.gif" alt="<?=text::get('MIN_BOTTOM_VIEW');?>" width="15" height="15" border="0" class="block"></td>
						<td><img src="img/ico_layout_3_disabled.gif" alt="<?=text::get('MIN_TOP_VIEW');?>" width="15" height="15" border="0" class="block"></td>
					</tr>
				</table>
			</div>
		</td>
	</tr>
</table>

</body>
