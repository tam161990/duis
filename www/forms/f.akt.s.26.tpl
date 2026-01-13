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
    
    foreach ($parsedData as $row) {
        $rowNum++;
        
        // Check if work type changed - show as group header
        $workType = isset($row[0]) ? trim($row[0]) : '';
        if ($workType !== $currentWorkType) {
            $currentWorkType = $workType;
            // Show work type header row
            ?>
            <tr class="table_head_2">
                <td colspan="3" style="padding: 8px; font-weight: bold;"><?= htmlspecialchars($workType); ?></td>
            </tr>
            <?
        }
        
        // Determine type and status
        $code = isset($row[1]) ? trim($row[1]) : '';
        $title = isset($row[2]) ? trim($row[2]) : '';
        $codeLength = strlen($code);
        $statusLabel = '';
        $statusColor = '';
        $rowClass = ($rowNum % 2 == 0) ? 'table_cell_3' : 'table_cell_2';
        
        if ($codeLength == 5 || empty($code)) {
            // WORK
            // Get work type ID for duplicate check
            $workTypeId = false;
            if (!empty($row[0])) {
                $workTypeId = dbProc::getWorkTypeIdByName($row[0]);
            }
            
            // Check status
            if (!empty($code)) {
                $workInfo = dbProc::getWorkInfoByCode($code);
                $existsInDarbi = dbProc::workExistsInDarbi($actId, $code, $workTypeId);
                
                if ($workInfo !== false && !$existsInDarbi) {
                    // Status 1: OK - inserted into darbi
                    $statusLabel = '<span style="color: green;">✓ ' . text::get('STATUS_SAVED') . '</span>';
                    $statusColor = 'background-color: #e8f5e9;';
                } elseif ($existsInDarbi) {
                    // Status 2: Already exists in darbi
                    $statusLabel = '<span style="color: orange;">⚠ ' . text::get('STATUS_EXISTS') . '</span>';
                    $statusColor = 'background-color: #fff3e0;';
                } else {
                    // Status 3: Not found in kl_kalkulacija
                    $statusLabel = '<span style="color: red;">✗ ' . text::get('STATUS_NOT_FOUND') . '</span>';
                    $statusColor = 'background-color: #ffebee;';
                }
            } else {
                // Empty code - worker row
                $statusLabel = '<span style="color: green;">✓ ' . text::get('STATUS_SAVED') . '</span>';
                $statusColor = 'background-color: #e8f5e9;';
            }
        } elseif ($codeLength == 8) {
            // MATERIAL
            // Get work type ID for duplicate check
            $workTypeId = false;
            if (!empty($row[0])) {
                $workTypeId = dbProc::getWorkTypeIdByName($row[0]);
            }
            
            // Check status for materials
            if (!empty($code)) {
                $materialInfo = dbProc::getMaterialInfoByCode($code);
                $existsInMateriali = dbProc::materialExistsInMateriali($actId, $code, $workTypeId);
                
                if ($materialInfo !== false && !$existsInMateriali) {
                    // Status 1: OK - inserted into materiali
                    $statusLabel = '<span style="color: green;">✓ ' . text::get('STATUS_SAVED') . '</span>';
                    $statusColor = 'background-color: #e8f5e9;';
                } elseif ($existsInMateriali) {
                    // Status 2: Already exists in materiali
                    $statusLabel = '<span style="color: orange;">⚠ ' . text::get('STATUS_EXISTS') . '</span>';
                    $statusColor = 'background-color: #fff3e0;';
                } else {
                    // Status 3: Not found in kl_materiali
                    $statusLabel = '<span style="color: red;">✗ ' . text::get('STATUS_NOT_FOUND') . '</span>';
                    $statusColor = 'background-color: #ffebee;';
                }
            } else {
                // Empty code - worker row
                $statusLabel = '<span style="color: green;">✓ ' . text::get('STATUS_SAVED') . '</span>';
                $statusColor = 'background-color: #e8f5e9;';
            }
        } else {
            $statusLabel = '<span style="color: gray;">?</span>';
            $statusColor = '';
        }
    ?>
        <tr class="<?=$rowClass;?>" style="<?=$statusColor;?>">
            <td width="15%" align="center"><?=$statusLabel;?></td>
            <td width="15%" align="center"><?= htmlspecialchars($code); ?></td>
            <td width="70%" align="left"><?= htmlspecialchars($title); ?></td>
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
