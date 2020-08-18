
<div id="dhtmltooltip"></div>

<script type="text/javascript">

/***********************************************
* Cool DHTML tooltip script- © Dynamic Drive DHTML code library (www.dynamicdrive.com)
* This notice MUST stay intact for legal use
* Visit Dynamic Drive at http://www.dynamicdrive.com/ for full source code
***********************************************/

var offsetxpoint=-60 //Customize x offset of tooltip
var offsetypoint=20 //Customize y offset of tooltip
var ie=document.all
var ns6=document.getElementById && !document.all
var enabletip=false
if (ie||ns6)
var tipobj=document.all? document.all["dhtmltooltip"] : document.getElementById? document.getElementById("dhtmltooltip") : ""

function ietruebody(){
return (document.compatMode && document.compatMode!="BackCompat")? document.documentElement : document.body
}

function ddrivetip(thetext, thecolor, thewidth){
if (ns6||ie){
if (typeof thewidth!="undefined") tipobj.style.width=thewidth+"px"
if (typeof thecolor!="undefined" && thecolor!="") tipobj.style.backgroundColor=thecolor
tipobj.innerHTML=thetext
enabletip=true
return false
}
}

function positiontip(e){
if (enabletip){
var curX=(ns6)?e.pageX : event.clientX+ietruebody().scrollLeft;
var curY=(ns6)?e.pageY : event.clientY+ietruebody().scrollTop;
//Find out how close the mouse is to the corner of the window
var rightedge=ie&&!window.opera? ietruebody().clientWidth-event.clientX-offsetxpoint : window.innerWidth-e.clientX-offsetxpoint-20
var bottomedge=ie&&!window.opera? ietruebody().clientHeight-event.clientY-offsetypoint : window.innerHeight-e.clientY-offsetypoint-20

var leftedge=(offsetxpoint<0)? offsetxpoint*(-1) : -1000

//if the horizontal distance isn't enough to accomodate the width of the context menu
if (rightedge<tipobj.offsetWidth)
//move the horizontal position of the menu to the left by it's width
tipobj.style.left=ie? ietruebody().scrollLeft+event.clientX-tipobj.offsetWidth+"px" : window.pageXOffset+e.clientX-tipobj.offsetWidth+"px"
else if (curX<leftedge)
tipobj.style.left="5px"
else
//position the horizontal position of the menu where the mouse is positioned
tipobj.style.left=curX+offsetxpoint+"px"

//same concept with the vertical position
if (bottomedge<tipobj.offsetHeight)
tipobj.style.top=ie? ietruebody().scrollTop+event.clientY-tipobj.offsetHeight-offsetypoint+"px" : window.pageYOffset+e.clientY-tipobj.offsetHeight-offsetypoint+"px"
else
tipobj.style.top=curY+offsetypoint+"px"
tipobj.style.visibility="visible"
}
}

function hideddrivetip(){
if (ns6||ie){
enabletip=false
tipobj.style.visibility="hidden"
tipobj.style.left="-1000px"
tipobj.style.backgroundColor=''
tipobj.style.width=''
}
}

document.onmousemove=positiontip

</script>


<?= $oFormWorkTab -> getFormHeader(); ?>
<table cellpadding="5" cellspacing="1" border="0" width="100%">
	<tr>
		<td align=center colspan="2"><?= $oFormWorkTab -> getMessage(); ?></td>
	</tr>


<tr>
	<td align=center>
	<table width="100%">
		<tr>
			<td><h1><?=text::toUpper(text::get(TAB_WORKS));?></h1></td>
			<? if($trase == 1) {   ?>
<td>
<table cellpadding="5" cellspacing="1" border="0" width="100%">
<tr>
<td width="12%" class="table_cell_c"><?= $oFormWorkTab-> getElementLabel('sum_m3'); ?></td>
<td width="13%" class="table_cell_2"><?= $oFormWorkTab-> getElementHtml('sum_m3'); ?></td>
<td width="12%" class="table_cell_c"><?= $oFormWorkTab-> getElementLabel('sum_ha'); ?></td>
<td width="13%" class="table_cell_2"><?= $oFormWorkTab-> getElementHtml('sum_ha'); ?></td>
<td width="12%" class="table_cell_c"><?= $oFormWorkTab-> getElementLabel('sum_km'); ?></td>
<td width="13%" class="table_cell_2"><?= $oFormWorkTab-> getElementHtml('sum_km'); ?></td>
<td width="12%" class="table_cell_c"><?= $oFormWorkTab-> getElementLabel('sum_gab'); ?></td>
<td width="13%" class="table_cell_2"><?= $oFormWorkTab-> getElementHtml('sum_gab'); ?></td>
</tr>
</table>
</td>
<? } ?>
		</tr>
	</table>
	</td>
	<td></td>
</tr>
    <tr>
		<td valign="top">
        <?
        $x = 0;
        foreach ($aWorks as $d => $aDayWorks)
            {
        ?>
        <table cellpadding="5" cellspacing="1" border="0" width="100%">
		   <tr class="table_head_2">

                <th width="10%"><?=text::get('CHIPHER');?></th>
                <? if(!$tame) { ?>
					<th  width="15%"><?=text::get('FINISHING_DATE');?></th>
				<? } ?>
				<th width="32%" colspan="2"><?=text::get('NAME');?></th>
				<th  width="15%"><?=text::get('PRICE');?></th>
                <th  width="10%"><?=text::get('UNIT_OF_MEASURE');?></th>
                <th  width="15%"><?=text::get('AMOUNT');?></th>
                <? if($tame) { ?>
                    <th  width="15%"><?=text::get('AMOUNT_KOR');?></th>
                <? } ?>
				<th  width="15%"><?=text::get('PRICE_TOTAL');?></th>
			 	<th width="3%">&nbsp;</th>
			</tr>

            <?
            foreach ($aDayWorks as $j => $actWork)
            { 
                
                if($tame && $actWork['DRBI_DAUDZUMS'] != $actWork['DRBI_DAUDZUMS_KOR'] ) {
                ?>
                <tr class="table_cell_3"  style="font-weight:bold;" id="blank_work<?= $i; ?>">
                <?
                } else {
                ?>
                <tr class="table_cell_3"  id="blank_work<?= $i; ?>">
                <?    
                }
                ?>
				<td>
                    <?= $oFormWorkTab->getElementHtml('id['.$x.']'); ?>
                    <?= $oFormWorkTab->getElementHtml('chipher['.$x.']'); ?>
                </td>
                <? if(!$tame) { ?>
					<td><?= $oFormWorkTab->getElementHtml('plan_date['.$x.']'); ?></td>					
				<? }  ?>			
                <td width="40%"><?= $oFormWorkTab->getElementHtml('title['.$x.']'); ?> </td>
                <? if(!$tame) { ?>
                <td width="20"><div onMouseover="ddrivetip('<?= $actWork['KKAL_APRAKSTS']; ?>', '#EFEFEF')";     onMouseout="hideddrivetip()" style="text-align:right;"><img src="img/info.PNG" alt="" width="16" height="16"></div> </td>
                <? } else { ?>
                    <td></td>		
                 <? } ?>	
                <td><?= $oFormWorkTab->getElementHtml('standart['.$x.']'); ?></td>
                <td><?= $oFormWorkTab->getElementHtml('measure['.$x.']'); ?></td>
				<? if($tame) { ?>
					<td><?= $oFormWorkTab->getElementHtml('amount_k['.$x.']'); ?></td>
					<td><?= $oFormWorkTab->getElementHtml('amount_kor['.$x.']'); ?></td>
				<? } else { ?>
					<td><?= $oFormWorkTab->getElementHtml('amount['.$x.']'); ?></td>
				<? } ?> 
				<td><?= $oFormWorkTab->getElementHtml('total['.$x.']'); ?></td>
             	<td>
                    <? if(empty($actWork['DRBI_APPROVE_DATE']) || $tame)  {?>
                    <?= $oFormWorkTab->getElementHtml('work_del['.$x.']'); ?>
                    <? } else{ ?>
                    &nbsp;
                    <? } ?>
                </td>
			</tr>

        <?
        $x++;
        }
        ?>
        <tr>
             <td align="right" colspan="2"><b><?=text::get('WORK_APPROVE_DATE');?>:</b></td>
	     <td align="left" colspan="2"><b><?= isset($workApproveDate[$d])?$workApproveDate[$d]:''; ?></b></td>

             <td align="right" colspan="3"><b><?=text::get('TOTAL');?>:</b></td>
             <td align="center"><b><?= isset($totalTime[$d])?$totalTime[$d]:''; ?></b></td>
        </tr>
        <?
		}
		?>
	    </table>
        </td>
        <td width="20%"  valign="top">
            <table cellpadding="5" cellspacing="1" border="0" align="center" width="100%">
            <? if(!$isReadonly)  {
                if($tame == false) {
                    ?>
                <tr>
                    <td bgcolor="white"><?= $oFormWorkTab->getElementHtml('tameLink'); ?></td>
                </tr>
                <? }
              foreach($calcGroups as $i=>$val){?>
             <tr>
                <td bgcolor="white"><?= $oFormWorkTab->getElementHtml('group['.$i.']'); ?></td>
             </tr>
            <? }} ?>
            </table>
            <br />
            <table cellpadding="5" cellspacing="0" border="0" align="center">
            <tr>
             <? if(!$isReadonly)  {?>
            	<td><?= $oFormWorkTab -> getElementHtml('save'); ?></td>
             <? } ?>
            
             </tr>
            </table>
        </td>
	</tr>

</table>
<?= $oFormWorkTab -> getFormBottom(); ?>

