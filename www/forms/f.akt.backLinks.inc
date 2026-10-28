<?
// Builds $actSearchLink and $actListLink for Atpakal (BACK) from act forms.
// Requires: $actId; optional $isSearch, $searchNum from parent scope.

include_once('f.akt.rbfSearchCtx.inc');

$fromRbfSearch = reqVar::get('fromRbfSearch');
$isSearchBack = reqVar::get('isSearch');
if ($isSearchBack === false && isset($isSearch))
{
    $isSearchBack = $isSearch;
}
$searchNumBack = reqVar::get('searchNum');
if ($searchNumBack === false && isset($searchNum))
{
    $searchNumBack = $searchNum;
}

if ($fromRbfSearch == 1)
{
    $oLink = new urlQuery();
    $oLink->addPrm('isSearch', 1);
    $oLink->addPrm('isReturn', 1);
    $oLink->addPrm('selectedId', $actId);
    foreach ($aktRbfSrchCtxMap as $urlKey => $hiddenName)
    {
        $oLink->addPrm($urlKey, aktRbfSearchCtxValue($urlKey));
    }
    $oLink->addPrm(FORM_ID, 'f.akt.s.35');
    $actSearchLink = $oLink->getQuery();
    unset($oLink);

    $oLink = new urlQuery();
    $oLink->addPrm('selectedId', $actId);
    foreach ($aktRbfSrchCtxMap as $urlKey => $hiddenName)
    {
        $oLink->addPrm($urlKey, aktRbfSearchCtxValue($urlKey));
    }
    $oLink->addPrm(FORM_ID, 'f.akt.s.35');
    $actListLink = $oLink->getQuery();
    unset($oLink);
}
else
{
    $oLink = new urlQuery();
    $oLink->addPrm('isSearch', $isSearchBack);
    if ($isSearchBack == 1 || $isSearchBack == 3)
    {
        $oLink->addPrm('isReturn', 1);
    }
    $oLink->addPrm('selectedId', ($isSearchBack == 1 || $isSearchBack == 3) ? $actId : $searchNumBack);
    $oLink->addPrm(FORM_ID, 'f.akt.s.9');
    $actSearchLink = $oLink->getQuery();
    unset($oLink);

    $oLink = new urlQuery();
    $oLink->addPrm('isNumber', ($isSearchBack == 1 || $isSearchBack == 3) ? 0 : $searchNumBack);
    $oLink->addPrm('selectedId', $actId);
    $oLink->addPrm(FORM_ID, 'f.akt.s.9');
    $actListLink = $oLink->getQuery();
    unset($oLink);
}
?>
