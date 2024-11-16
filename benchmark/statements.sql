select * from mem_10k;
select * from mem_10k where EID > 1628780806 AND EID < 1658105202;
select count(*) from mem_10k;
select * from mem_10k where EID = 'Saturday' OR EID = 'Sunday';
select window(1 day) as one_day, count(*) from mem_10k group by one_day;
select window(1 month) as one_month, count(*) from mem_10k group by one_month;
select * from mem_10k where EID > 1658105202;
select window(1 day) as one_day, count(*) from mem_10k where EID > 1641936187 and EID < 1652395282 group by one_day;
select window(1 day) as one_day, count(*) from <log> where EID = 'Monday' and EID > 1641936187 and EID < 1652395282 group by one_day;