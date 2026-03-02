<body class="frame_1">
<?= $oFormPop -> getFormHeader(); ?>
<?=$oFormPop->getElementHtml('jsRefresh2');?>
<h1><?=text::toUpper(text::get('UPLOAD_ESTIMATE'));?></h1>
<div align=center><?= $oFormPop -> getMessage(); ?></div>

<table cellpadding="5" cellspacing="1" border="0" width="100%">
    <tr>
        <td class="table_cell_c" width="20%"><img src="img/ico_excel.gif" alt="" width="16" height="16">&nbsp;<?= $oFormPop -> getElementLabel('fileName'); ?>:</td>
        <td class="table_cell_2" width="80%"><?= $oFormPop -> getElementHtml('fileName'); ?></td>
    </tr>
</table>

<? if (!empty($parsedData) && $hasFile) { ?>
<table cellpadding="5" cellspacing="1" border="0" width="100%">
    <tbody>
    <?
    $currentWorkType = '';
    $rowNum = 0;
    
    foreach ($parsedData as $rowIndex => $row) {
        $rowNum++;
        
        // Check if work type changed - show as group header
        // row[0] = Section Type, row[1] = Group Type
        $workType = isset($row[1]) ? trim($row[1]) : '';
        if ($workType !== $currentWorkType) {
            $currentWorkType = $workType;
            // Show work type header row
            ?>
            <tr class="table_head_2">
                <td colspan="3" style="padding: 8px; font-weight: bold;"><?= htmlspecialchars($workType); ?></td>
            </tr>
            <?
        }
        
        // Get status from tracked statuses array
        // row[0] = Section Type (1=WORK, 2=MATERIAL), row[2] = Code, row[3] = Title, row[5] = Amount
        $sectionType = isset($row[0]) ? $row[0] : null;
        $code = isset($row[2]) ? trim($row[2]) : '';
        $title = isset($row[3]) ? trim($row[3]) : '';
        $codeLength = strlen($code);
        $statusLabel = '';
        $statusColor = '';
        $rowClass = ($rowNum % 2 == 0) ? 'table_cell_3' : 'table_cell_2';
        
        // Get status from processing (defaults to saved for worker rows)
        $status = isset($rowStatuses[$rowIndex]) ? $rowStatuses[$rowIndex] : 1;
        $amount = isset($row[5]) ? trim($row[5]) : null;
        $amountNotSet = (empty($amount) || $amount === '0' || $amount === 0);
        
        // Determine status display based on section type
        if ($sectionType == 1 || ($sectionType === null && ($codeLength == 5 || empty($code)))) {
            // WORK
            switch ($status) {
                case 1: // Saved successfully
                    $statusLabel = '<span style="color: green;">✓ ' . text::get('STATUS_SAVED') . '</span>';
                    $statusColor = 'background-color: #e8f5e9;';
                    break;
                case 2: // Already exists
                    $statusLabel = '<span style="color: orange;">⚠ ' . text::get('STATUS_WORK_EXISTS') . '</span>';
                    $statusColor = 'background-color: #fff3e0;';
                    break;
                case 3: // Not found in catalog
                    $statusLabel = '<span style="color: red;">✗ ' . text::get('STATUS_WORK_NOT_FOUND') . '</span>';
                    $statusColor = 'background-color: #ffebee;';
                    break;
                case 4: // Amount not set
                    $statusLabel = '<span style="color: red;">✗ ' . text::get('STATUS_AMOUNT_NOT_SET') . '</span>';
                    $statusColor = 'background-color: #ffebee;';
                    break;
                default:
                    $statusLabel = '<span style="color: gray;">?</span>';
                    $statusColor = '';
            }
        } elseif ($sectionType == 2 || ($sectionType === null && $codeLength == 8)) {
            // MATERIAL
            switch ($status) {
                case 1: // Saved successfully
                    $statusLabel = '<span style="color: green;">✓ ' . text::get('STATUS_SAVED') . '</span>';
                    $statusColor = 'background-color: #e8f5e9;';
                    break;
                case 2: // Already exists
                    $statusLabel = '<span style="color: orange;">⚠ ' . text::get('STATUS_MATERIAL_EXISTS') . '</span>';
                    $statusColor = 'background-color: #fff3e0;';
                    break;
                case 3: // Not found in catalog
                    $statusLabel = '<span style="color: red;">✗ ' . text::get('STATUS_MATERIAL_NOT_FOUND') . '</span>';
                    $statusColor = 'background-color: #ffebee;';
                    break;
                case 4: // Amount not set
                    $statusLabel = '<span style="color: red;">✗ ' . text::get('STATUS_AMOUNT_NOT_SET') . '</span>';
                    $statusColor = 'background-color: #ffebee;';
                    break;
                default:
                    $statusLabel = '<span style="color: gray;">?</span>';
                    $statusColor = '';
            }
        } else {
            $statusLabel = '<span style="color: gray;">?</span>';
            $statusColor = '';
        }
    ?>
        <tr class="<?=$rowClass;?>" style="<?=$statusColor;?>">
            <td width="30%" align="center"><?=$statusLabel;?></td>
            <td width="10%" align="center"><?= htmlspecialchars($code); ?></td>
            <td width="60%" align="left"><?= htmlspecialchars($title); ?></td>
        </tr>
    <?
    }
    ?>
    </tbody>
</table>
<? } ?>

<table cellpadding="5" cellspacing="0" border="0" align="center">
    <tr>
        <td><?=$oFormPop->getElementHtml('upload');?></td>
        <td><?=$oFormPop->getElementHtml('close');?></td>
    </tr>
</table>
<?= $oFormPop->getFormBottom(); ?>
<?=$oFormPop->getElementHtml('jsButtonsControl');?>
</body>
