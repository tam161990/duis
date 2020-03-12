<body class="head">
<?= $oForm -> getFormHeader(); ?>
<table cellpadding="0" cellspacing="0" border="0" align="center" height="100%" width="400">
<tr><td  height="15%">&nbsp;</td></tr>

<tr><td  height="5%" align="center"><?= $oForm -> getErrors(); ?></td></tr>
<tr><td height="20%" >
<table cellpadding="1" cellspacing="0" border="0" align="center"  width="270" bgcolor="#d1d1d" >
    <tr><td>
    <table cellpadding="3" cellspacing="0" border="0" align="center"  width="100%" bgcolor="#eeeeee" >
       <tr><td style="padding-left:30px;"><img src="/img/st.gif" alt="" width="70" vspace="5" class="block"></td></tr>
       <tr><td style="padding-right:30px;" align="right"><img src="/img/start.gif" alt="<?=text::get('APPLICATION_NAME');?>" width="176" height="59"  class="block"></td></tr>
        <tr>
    		<td style="padding-left:33px; color:#666666"><?= $oForm -> getElementLabel('login') ?>:</td>
        </tr>
    	<tr>
    		<td><?= $oForm -> getElementHtml('login'); ?></td>
       	</tr>
    	<tr>
    		<td style="padding-left:33px; color:#666666"><?= $oForm -> getElementLabel('password'); ?>:</td>
        </tr>
    	<tr>
    		<td><?= $oForm -> getElementHtml('password'); ?></td>
        </tr>
    	<tr>
    		<td style="padding-left:33px;"><?= $oForm -> getElementHtml('submit'); ?></td>
    	</tr>
        <tr><td>&nbsp;</td></tr>
    </table>
   </td></tr>
</table>
</td></tr>

<tr><td height="25%">
<table cellpadding="0" cellspacing="3" border="0" align="center" >
	<tr>
		<td width="41"><?= $oForm -> getElementHtml('warningIcon'); ?>&nbsp;</td>
        <td><?= $oForm -> getElementHtml('warning'); ?>&nbsp;</td>
	</tr>
</table>
</td></tr>
<tr><td height="5%">
<table cellpadding="0" cellspacing="3" border="0" align="center"  color="#666666">
	<tr>

        <td><a href="" target="new" style="color: #666666;"><?= $oForm -> getElementLabel('instruction'); ?></a>&nbsp;|&nbsp;</td>
        <td><a href="" target="new" style="color: #666666;"><?= $oForm -> getElementLabel('problem'); ?></a></td>
	</tr>
</table>
</td></tr>
</table>
<?= $oForm -> getFormBottom(); ?>
<script language="JavaScript">
if(document.all['login'].value != '')
{
	document.all['password'].focus();
}
else
{
	document.all['login'].focus();
}
var openInFrame = this.name;
if((openInFrame == 'frameTop')||(openInFrame == 'frame_1')||(openInFrame == 'frame_2')||(openInFrame == 'frameButtons') )  
{
	parent.location.reload();
}
</script>
</body>