<body class="frame_2">
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
    <table cellpadding="0" cellspacing="0" border="0" width="100%">
        <tr>
            <td><h1><?= text::toUpper(text::get('EVENT_LOG')); ?></h1></td>
            
        </tr>
    </table>

    <table cellpadding="5" cellspacing="1" border="0" width="100%" >
        <tr class="table_head_2">
            <td width="10%"><?= text::get('DATE'); ?></td>
            <td width="5%"><?= text::get('TYPE'); ?></td>
            <td width="10%"><?=text::get('EVENT_MODULE');?></td>
            <td width="15%"><?=text::get('USER');?></td>
            <td width="15%"><?= text::get('EVENT_SECTION'); ?></td>
            <td width="45%"><?= text::get('DESCRIPTION'); ?></td>
        </tr>
    <?
        if (is_array($res) && count($res) > 0)
        {
            foreach ($res as $row)
            {
    ?> 
            <tr class="table_cell_3" >
                <td align="center"><?= $row['EVNT_TIMESTAMP']; ?></td>
                <td align="center"><?= $row['EVNT_TYPE']; ?></td>
                <td align="left"><?= $row['MODULE_TITLE']; ?></td>
                <td align="left"><?= $row['USER_NAME']; ?></td>
                <td align="left"><?= $row['FORM_NAME']; ?></td>
                <td align="left"><?= $row['DESCRIPTION']; ?></td>        
            </tr>
                
        <? }
    }?>
    
    </table>    
</body>