<?
// f.akt.s.35 search criteria on act forms: hidden names must not clash with act fields (employeeCode, status, …).
$aktRbfSrchCtxMap = array(
    'employeeCode' => 'srchEmployeeCode',
    'vvNumber' => 'srchVvNumber',
    'territoryCode' => 'srchTerritoryCode',
    'actType' => 'srchActType',
    'authorId' => 'srchAuthorId',
    'status' => 'srchStatus',
);

if (!function_exists('aktRbfSearchCtxValue'))
{
    function aktRbfSearchCtxValue($urlKey)
    {
        global $aktRbfSrchCtxMap;
        if (!isset($aktRbfSrchCtxMap[$urlKey]))
        {
            return '-1';
        }
        $hiddenName = $aktRbfSrchCtxMap[$urlKey];
        $v = reqVar::get($hiddenName);
        if ($v !== false && $v !== '')
        {
            return $v;
        }
        $v = reqVar::get($urlKey);
        return ($v !== false && $v !== '') ? $v : '-1';
    }
}

if (!function_exists('aktRbfSearchCtxRaw'))
{
    /** Value for hidden field (empty string if unset). */
    function aktRbfSearchCtxRaw($urlKey)
    {
        global $aktRbfSrchCtxMap;
        $hiddenName = $aktRbfSrchCtxMap[$urlKey];
        $v = reqVar::get($hiddenName);
        if ($v !== false && $v !== '')
        {
            return $v;
        }
        $v = reqVar::get($urlKey);
        return ($v !== false) ? $v : '';
    }
}
?>
