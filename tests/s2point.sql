
begin;
select plan(1);

select is(pg_typeof('(1,2,3)'::s2point)::text, 's2point', 's2point_in');
    
select * from finish();
rollback;
