
INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`) VALUES 
('PERS_NUMBER', 'Pers numurs');

update kl_writeoff_code set KWRC_TITLE = '71882 Dabas stihiju radīto avārijas bojājumu novēršana'
where KWRC_KAKV_ID = 6 and kwrc_kobj_id <> 9;

update kl_writeoff_code set KWRC_TITLE = '71882 Dabas stihiju radīto avārijas bojājumu novēršana  / objekta kods K00'
where KWRC_KAKV_ID = 7 and kwrc_kobj_id <> 9;

insert into kl_writeoff_code(KWRC_KAKV_ID, KWRC_KOBJ_ID, KWRC_TITLE)
values(3, 98, '71889 Trešo personu radīto zaudējumu bojājumu novēršana');
insert into kl_writeoff_code(KWRC_KAKV_ID, KWRC_KOBJ_ID, KWRC_TITLE)
values(6, 98, '71889 Trešo personu radīto zaudējumu bojājumu novēršana');
insert into kl_writeoff_code(KWRC_KAKV_ID, KWRC_KOBJ_ID, KWRC_TITLE)
values(7, 98, '71889 Trešo personu radīto zaudējumu bojājumu novēršana');

ALTER TABLE `AKTI` ADD COLUMN  `RAKT_PERS_NUMBER` VARCHAR(100) NULL;