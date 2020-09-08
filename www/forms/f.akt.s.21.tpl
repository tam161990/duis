
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

<h1><?=text::toUpper(text::get(TAB_WORKS));?></h1>
<?= $oFormWorkTab -> getFormHeader(); ?>
<table cellpadding="5" cellspacing="1" border="0" width="100%">
	<tr>
		<td align=center colspan="2"><?= $oFormWorkTab -> getMessage(); ?></td>
	</tr>
    <tr>
		<td valign="top">
        <?
        $x = 0;
        foreach ($aWorks as $d => $aGroupWorks)
        {
        ?>
        <table cellpadding="5" cellspacing="1" border="0" width="100%">
		   <tr class="table_head_2">

                <th width="10%"><?=text::get('CHIPHER');?></th>
                <th width="20%"><?=text::get('SINGLE_WORK_TYPE');?></th>
                <th width="15%"><?=text::get('PROJECT_OBJECT_TITLE');?></th>
				<th width="20%" ><?=text::get('NAME');?></th>
                <th  width="7%"><?=text::get('UNIT_OF_MEASURE');?></th>
				<th  width="10%"><?=text::get('AMOUNT');?></th>                
                <th  width="15%"><?=text::get('COMMENT');?></th>
                <? if( ($status == STAT_CLOSE && ($isAdmin || $isEconomist || $projectApprover)))  {?>
                <th  width="3%"><?=text::get('PROJECT_EXPORT_TYPE');?></th>
                <? } else {?>
                 <th width="3%">&nbsp;</th>
                 <? } ?>
			</tr>

	  <?
        foreach ($aGroupWorks as $j => $actWork)
		{
		
            $changestyle = "font-weight:normal;"   ;
            if($actWork['DRBI_IS_WORKER'] == 1)
            {
                $pricestyle = "color:#e4edd8;  font-size:1px;"   ;
            ?>
            <tr class="table_cell_4" style="<?=$changestyle;?>" id="blank_mat<?= $i; ?>">

            <?} else
            {
                $pricestyle = "color:#ffffff;  font-size:11px;"   ;
            ?>
            <tr class="table_cell_3" style="<?=$changestyle;?>" id="blank_mat<?= $i; ?>">
            <?}
         ?>

				<td>
                    <?= $oFormWorkTab->getElementHtml('id['.$x.']'); ?>
                    <?= $oFormWorkTab->getElementHtml('chipher['.$x.']'); ?>
                </td>
                <td><?= $oFormWorkTab->getElementHtml('work_type['.$x.']'); ?> </td>   
                <td><?= $oFormWorkTab->getElementHtml('work_type_text['.$x.']'); ?> </td>   
				<td><?= $oFormWorkTab->getElementHtml('title['.$x.']'); ?> </td>                
				<td><?= $oFormWorkTab->getElementHtml('measure['.$x.']'); ?></td>
				<td><?= $oFormWorkTab->getElementHtml('amount['.$x.']'); ?></td>                
                <td><?= $oFormWorkTab->getElementHtml('notes['.$x.']'); ?></td>
                <? if( ($status == STAT_CLOSE && ($isAdmin || $isEconomist || $projectApprover)))  {?>
                    <td><?= $oFormWorkTab->getElementHtml('export_type['.$x.']'); ?></td>
                <? } else {?>
                    <td>
                        <? if(!$isReadonly)  {?>
                        <?= $oFormWorkTab->getElementHtml('work_del['.$x.']'); ?>
                        <? } else{ ?>
                        &nbsp;
                        <? } ?>
                    </td>
                <? } ?>
             	
			</tr>
            <?
            $x++;
            }
            ?>
            <tr>
                 <td align="right" colspan="8">&nbsp;</td>
            </tr>
            <?
           
		}
		?>
       
	    </table>
        </td>
        <td width="20%"  valign="top">
            <table cellpadding="5" cellspacing="1" border="0" align="center" width="100%">
            <? if(!$isReadonly)  {
              foreach($calcGroups as $i=>$val){?>
             <tr>
                <td bgcolor="white"><?= $oFormWorkTab->getElementHtml('group['.$i.']'); ?></td>
             </tr>
            <? }} ?>
            </table>
            <br />
            <table cellpadding="5" cellspacing="0" border="0" align="center">
            <tr>
             <? if(!$isReadonly || ($status == STAT_CLOSE && ($isAdmin || $isEconomist || $projectApprover)))  {?>
            	<td><?= $oFormWorkTab -> getElementHtml('save'); ?></td>
             <? } ?>
            
             </tr>
            </table>
        </td>
	</tr>

</table>
<?= $oFormWorkTab -> getFormBottom(); ?>

