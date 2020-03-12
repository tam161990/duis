<body class="head">

<img src="img/0.gif" alt="" width="1" height="250" class="block">

<table width="100%">
	<tr>
		<td align="center" valign="middle">
			
			<table width="340" cellpadding="10" cellspacing="0" border="0">
				<tr>
					<td><img src="img/big_error.gif" alt="Kļūda" width="60" height="90"></td>
					<td><?=text::get('CRITICAL_ERROR_MESSAGE');?><br><br>
					<font color="#716F60"><?=text::get('REASON');?>: <?=$errorMessage;?> </font>
					<br><br></td>
				</tr>
			</table>
			
		</td>
	</tR>	
</table>

</body>
