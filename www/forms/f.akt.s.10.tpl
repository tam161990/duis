<script type="text/javascript">

	/***********************************************
	* Cool DHTML tooltip script II- (c) Dynamic Drive DHTML code library (www.dynamicdrive.com)
	* Please keep this notice intact
	* Visit Dynamic Drive at http://www.dynamicdrive.com/ for full source code
	***********************************************/
	
	var offsetfromcursorX=12 //Customize x offset of tooltip
	var offsetfromcursorY=10 //Customize y offset of tooltip
	
	var offsetdivfrompointerX=10 //Customize x offset of tooltip DIV relative to pointer image
	var offsetdivfrompointerY=14 //Customize y offset of tooltip DIV relative to pointer image. Tip: Set it to (height_of_pointer_image-1).
	
	document.write('<div id="dhtmltooltip2"></div>') //write out tooltip DIV
	document.write('<img id="dhtmlpointer" src="img/arrow2.gif">') //write out pointer image
	
	var ie=document.all
	var ns6=document.getElementById && !document.all
	var enabletip=false
	if (ie||ns6)
	var tipobj=document.all? document.all["dhtmltooltip2"] : document.getElementById? document.getElementById("dhtmltooltip2") : ""
	
	var pointerobj=document.all? document.all["dhtmlpointer"] : document.getElementById? document.getElementById("dhtmlpointer") : ""
	
	function ietruebody(){
	return (document.compatMode && document.compatMode!="BackCompat")? document.documentElement : document.body
	}
	
	function ddrivetip(thetext, thewidth, thecolor){
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
	var nondefaultpos=false
	var curX=(ns6)?e.pageX : event.clientX+ietruebody().scrollLeft;
	var curY=(ns6)?e.pageY : event.clientY+ietruebody().scrollTop;
	//Find out how close the mouse is to the corner of the window
	var winwidth=ie&&!window.opera? ietruebody().clientWidth : window.innerWidth-20
	var winheight=ie&&!window.opera? ietruebody().clientHeight : window.innerHeight-20
	
	var rightedge=ie&&!window.opera? winwidth-event.clientX-offsetfromcursorX : winwidth-e.clientX-offsetfromcursorX
	var bottomedge=ie&&!window.opera? winheight-event.clientY-offsetfromcursorY : winheight-e.clientY-offsetfromcursorY
	
	var leftedge=(offsetfromcursorX<0)? offsetfromcursorX*(-1) : -1000
	
	//if the horizontal distance isn't enough to accomodate the width of the context menu
	if (rightedge<tipobj.offsetWidth){
	//move the horizontal position of the menu to the left by it's width
	tipobj.style.left=curX-tipobj.offsetWidth+"px"
	nondefaultpos=true
	}
	else if (curX<leftedge){
	tipobj.style.left="5px"
	}
	else{
	//alert(curX);
	//alert(offsetfromcursorX);
	//alert(offsetdivfrompointerX);
	//position the horizontal position of the menu where the mouse is positioned
	tipobj.style.left=curX+offsetfromcursorX-offsetdivfrompointerX+"px"
	pointerobj.style.left=curX+offsetfromcursorX+"px"
	//alert(tipobj.style.left);
	//alert(pointerobj.style.left);
	}
	
	//same concept with the vertical position
	if (bottomedge<tipobj.offsetHeight){
	tipobj.style.top=curY-tipobj.offsetHeight-offsetfromcursorY+"px"
	nondefaultpos=true
	}
	else{
	//alert(curY);
	//alert(offsetfromcursorY);
	//alert(offsetdivfrompointerY);
	tipobj.style.top=curY+offsetfromcursorY+offsetdivfrompointerY+"px"
	pointerobj.style.top=curY+offsetfromcursorY+"px"
	//alert(tipobj.style.top);
	//alert(pointerobj.style.top);
	}
	tipobj.style.visibility="visible"
	//alert(nondefaultpos);
	if (!nondefaultpos) {
	pointerobj.style.visibility="visible"
	//alert(pointerobj.style.visibility);
	}
	else{
	pointerobj.style.visibility="hidden"
	}
	}
	}
	
	function hideddrivetip(){
	if (ns6||ie){
	enabletip=false
	tipobj.style.visibility="hidden"
	pointerobj.style.visibility="hidden"
	tipobj.style.left="-1000px"
	tipobj.style.backgroundColor=''
	tipobj.style.width=''
	}
	}
	
	document.onmousemove=positiontip
	
	</script>
	
	<h1><?=text::toUpper(text::get(TAB_ESTIMATE));?></h1>
	<table cellpadding="5" cellspacing="1" border="0" width="100%">
		<?
			
		if (isset($fileInfo) && is_array($fileInfo))
		{
			for($i=0; $i<count($fileInfo); $i++)
			{
			?>
				<tr>
					<td class="table_cell" width="5%"><img src="img/<?=$fileInfo[$i]['ico'];?>" alt="" width="16" height="16">&nbsp;</td>
					<td class="table_cell_2" width="20%"><a href="<?=$fileInfo[$i]['getFileURL'];?>" ><?=$fileInfo[$i]['RFLS_NOSAUKUMS'];?></a></td>
					<td class="table_cell" ><?=text::get('DATE');?>:</td>
					<td class="table_cell_2" ><?=$fileInfo[$i]['RFLS_DATUMS'];?></td>
					<td class="table_cell" ><?=text::get('EXPORT_ACT_APOVE');?>:</td>
					<td class="table_cell_2" ><?=$fileInfo[$i]['AUTORS'];?></td>
					<? if($isProject == 1) { ?>
						<? if(isset($fileInfo[$i]['status'])) { ?>
							<td class="table_cell" ><?=text::get('STATUS');?>:</td>
						<? } else {  ?>
							<td class="table_cell" >&nbsp;</td>
						<? } ?>
						<td class="table_cell_2" ><?=$fileInfo[$i]['status'];?>
						<? if(!empty($fileInfo[$i]['error_msg'])) { ?>
							<div onMouseover="ddrivetip('<?= $fileInfo[$i]['error_msg'] ?>', 300);" onMouseout="hideddrivetip()" style="text-align:right;">
								<img src="img/info.PNG" alt="" width="16" height="16">
							</div>
						<? } ?>
						</td>
						<? if(!empty($fileInfo[$i]['project_no'])) { ?>
							<td class="table_cell" ><?=text::get('PROJECT_NO');?>:</td>
						<? } else {  ?>
							<td class="table_cell" >&nbsp;</td>
						<? } ?>
						<td class="table_cell_2" ><?=$fileInfo[$i]['project_no'];?></td>
					<? } ?>
				</tr>
	
			<?
			//if($isEditor && $isProject == 0) break;
			}
		}
		?>
	</table>
	
	
	