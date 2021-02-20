
UPDATE `AKTA_STATUSA_MAINA`  SET AAUD_DATUMS = '2020-12-20-00:00:00'
WHERE AAUD_RAKT_ID IN  (
						SELECT RAKT_ID FROM akti 
						WHERE RAKT_NUM_POSTFIX IN (
													'REM-118339',
													'REM-121685',
													'REM-124672',
													'REM-125058',
													'REM-128730',
													'REM-85116',
													'REM-135097',
													'REM-81736'
													) 
						AND `RAKT_IS_AUTO` = 0
						)
AND `AAUD_STATUS` = 'CLOSE'



UPDATE `darbi` SET
`DRBI_APPROVE_DATE` = '2020-12-20 00:00:00',
`DRBI_PLAN_DATE` = '2020-12-20 00:00:00',
`DRBI_WORK_APROVE_DATE` = '2020-12-20'
WHERE 1
AND `DRBI_RAKT_ID` IN (
SELECT RAKT_ID FROM akti WHERE RAKT_NUM_POSTFIX IN (
													'REM-118339',
													'REM-121685',
													'REM-124672',
													'REM-125058',
													'REM-128730',
													'REM-85116',
													'REM-135097',
													'REM-81736'
							)
							AND `RAKT_IS_AUTO` = 1
)

