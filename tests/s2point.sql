
begin;
select plan(3);

select is('(1,2,3)'::s2point, s2point(1,2,3), 's2point');
select is('(1,2,3)'::s2point::text, '(1,2,3)', 's2point_out');
select is(pg_typeof('(1,2,3)'::s2point)::text, 's2point', 's2point_in');
    
select * from finish();
rollback;
