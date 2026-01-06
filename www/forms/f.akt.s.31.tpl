
<?= $oFormWorkTab->getFormHeader(); ?>
<table cellpadding="5" cellspacing="1" border="0" width="100%">
    <tr>
		<td align="center" colspan="2"><?= $oFormWorkTab->getMessage(); ?></td>
    </tr>
    <tr>
        <td align="center">
            <table width="100%">
                <tr>
                    <td><h1><?= text::toUpper(text::get('RBF_WORKS_TAB')); ?></h1></td>
                </tr>
            </table>
        </td>
        <td></td>
    </tr>
    <tr>
		<td valign="top">
        <table cellpadding="5" cellspacing="1" border="0" width="100%">
		   <tr class="table_head_2">
                <th width="8%"><?= text::get('CHIPHER'); ?></th>
				<th width="10%"><?= text::get('FINISHING_DATE'); ?></th>
				<th width="25%"><?= text::get('NAME'); ?></th>
				<th width="8%"><?= text::get('PRICE'); ?></th>
                <th width="6%"><?= text::get('UNIT_OF_MEASURE'); ?></th>
                <th width="8%"><?= text::get('AMOUNT'); ?></th>
                <th width="10%"><?= text::get('PRICE_TOTAL'); ?></th>
                <? if($isAdmin) { ?>
                    <th width="8%"><?= text::get('CALC_WORK_H_NORM'); ?></th>
                    <th width="8%"><?= text::get('CALC_WORK_H_NORM_SUM'); ?></th>
				<? } ?>
				<th width="8%"><?= text::get('WRITE_OFF_ACCOUNT'); ?></th>
                <th width="4%"><?= text::get('ELEMENT'); ?></th>
                <th width="4%"><?= text::get('PERS'); ?></th>
			 	<th width="3%">&nbsp;</th>
			</tr>

            <?
            if($aWorkExist)
            {
                $x = 0;
                foreach ($aWorks as $j => $actWork)
                { 
                ?>
                <tr class="table_cell_3" id="blank_work<?= $x; ?>">
				<td>
                    <?= $oFormWorkTab->getElementHtml('id['.$x.']'); ?>
                    <?= $oFormWorkTab->getElementHtml('kid['.$x.']'); ?>
                    <?= $oFormWorkTab->getElementHtml('description['.$x.']'); ?>
                    <?= $oFormWorkTab->getElementHtml('chipher['.$x.']'); ?>
                </td>
				<td><?= $oFormWorkTab->getElementHtml('plan_date['.$x.']'); ?></td>					
                <td><?= $oFormWorkTab->getElementHtml('title['.$x.']'); ?></td>
                <td><?= $oFormWorkTab->getElementHtml('standart['.$x.']'); ?><?= $oFormWorkTab->getElementHtml('standart_display['.$x.']'); ?></td>
                <td><?= $oFormWorkTab->getElementHtml('measure['.$x.']'); ?></td>
				<td><?= $oFormWorkTab->getElementHtml('amount['.$x.']'); ?></td>
                <td><?= $oFormWorkTab->getElementHtml('total['.$x.']'); ?></td>
                <? if($isAdmin) { ?>
                    <td><?= $oFormWorkTab->getElementHtml('work_norm['.$x.']'); ?></td>
                    <td><?= $oFormWorkTab->getElementHtml('work_norm_sum['.$x.']'); ?></td>
				<? } ?>
				<td><?= $oFormWorkTab->getElementHtml('write_off_code['.$x.']'); ?></td>
                <td><?= $oFormWorkTab->getElementHtml('act_element['.$x.']'); ?></td>
                <td><?= $oFormWorkTab->getElementHtml('act_pers['.$x.']'); ?></td>					
             	<td>
                    <? if(!$isReadonly) { ?>
                    <?= $oFormWorkTab->getElementHtml('work_del['.$x.']'); ?>
                    <? } else { ?>
                    &nbsp;
                    <? } ?>
                </td>
			</tr>
        <?
        $x++;
        }
        ?>
        </table>
        <?
        }
        else
        {
        ?>
        <tr>
            <td colspan="13" class="table_cell_3" align="center">
                <i><?= text::get('RBF_WORKS_EMPTY'); ?></i>
            </td>
        </tr>
        </table>
        <?
        }
        ?>
        </td>
		<td valign="top" align="left">
			<table  cellpadding="5" cellspacing="1" border="0" align="center" width="100%">
		<?
		if(!$isReadonly)
		{
			foreach ($calcGroups as $i => $row)
			{
		?>
				<tr>
                    <td bgcolor="white"><?= $oFormWorkTab->getElementHtml('group['.$i.']'); ?></td>
                </tr>
		<?
			}
		}
		?>
			</table>
			<br />
			<table cellpadding="5" cellspacing="0" border="0" align="center">
			<tr>
		    <? if(!$isReadonly && $aWorkExist) { ?>
				<td><?= $oFormWorkTab->getElementHtml('save'); ?></td>
			<? } ?>
			</tr>
			</table>
		</td>
	</tr>
</table>

<?= $oFormWorkTab->getFormBottom(); ?>

