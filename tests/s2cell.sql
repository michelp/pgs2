
begin;
select plan(3);

select is('8800000000000001'::s2cell, s2cell('8800000000000001'), 's2cell');
select is('8800000000000001'::s2cell::text, '8800000000000001', 's2cell_out');
select is(pg_typeof('8800000000000001'::s2cell)::text, 's2cell', 's2cell_in');

select * from finish();
rollback;
