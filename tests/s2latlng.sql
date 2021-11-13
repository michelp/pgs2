begin;
select plan(1);

select is('{45, -90}'::s2latlng,
          s2latlng(0.7853981633974483,-1.5707963267948966),
          's2latlng rom degrees');

select * from finish();
rollback;
    

    
