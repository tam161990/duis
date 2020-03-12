<table cellpadding="5" cellspacing="0" border="0">
	<form action="<?=$url;?>" method="POST">
	<tr>
		<td nowrap><?=text::get('RECORDS_AMOUNT_ON_PAGE');?>:</td>
		<td><input type="text" name=<?=LISTING_AMOUNT_ON_PAGE_VAR;?> size="1" value="<?=$this->getAmountOnPage();?>" maxlength="3"></td>
		<td><img src="img/0.gif" border=0 width=15 height=1></td>
		<?
		if ($this->getCurrentPageNumber()>1)
		{
			?>
			<td><a href="<?=$url;?>&<?=LISTING_PAGE_NUMBER_VAR;?>=1&<?=LISTING_AMOUNT_ON_PAGE_VAR;?>=<?=$this->getAmountOnPage();?>"><img src="../img/ico_first.gif" alt="<?=text::get('TO_BEGIN');?>" width="6" height="7" class="block" border="0"></a></td>
			<td><a href="<?=$url;?>&<?=LISTING_PAGE_NUMBER_VAR;?>=<?=$this->getCurrentPageNumber()-1;?>&<?=LISTING_AMOUNT_ON_PAGE_VAR;?>=<?=$this->getAmountOnPage();?>"><img src="../img/ico_back.gif" alt="<?=text::get('PREVIOUS_PAGE');?>" width="9" height="7" class="block" border="0"></a></td>
			<?
		}
		?>
		<td nowrap><?= ($this -> getLastPosition() > 0) ? $this->getStartPosition()+1 : 0;?>..<?=$this->getLastPosition()+1;?> <?=text::get('FROM');?> <?=$this->getAmount();?></td>
		<?
		if ($this->getCurrentPageNumber()<$this->getLastPageNumber())
		{
			?>
			<td><a href="<?=$url;?>&<?=LISTING_PAGE_NUMBER_VAR;?>=<?=$this->getCurrentPageNumber()+1;?>&<?=LISTING_AMOUNT_ON_PAGE_VAR;?>=<?=$this->getAmountOnPage();?>"><img src="../img/ico_next.gif" alt="<?=text::get('NEXT_PAGE');?>" width="9" height="7" class="block" border="0"></a></td>
			<td><a href="<?=$url;?>&<?=LISTING_PAGE_NUMBER_VAR;?>=<?=$this->getLastPageNumber();?>&<?=LISTING_AMOUNT_ON_PAGE_VAR;?>=<?=$this->getAmountOnPage();?>"><img src="../img/ico_last.gif" alt="<?=text::get('TO_END');?>" width="6" height="7" class="block" border="0"></a></td>
			<?
		}
		?>
	</tr>
	</form>
</table>
