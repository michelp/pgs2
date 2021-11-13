begin;
select plan(6);

select is('8800000000000001'::s2cell::s2latlng,
          '(0.7853981627765666,-1.570796326174015)'::s2latlng,
          's2cell_to_s2latlng');

select is('8800000000000001'::s2cell::s2point,
          '(4.3902967226106497e-10,-0.7071067816255772,0.7071067807475178)'::s2point,
          's2cell_to_s2point');

select is('(4.3902967226106497e-10,-0.7071067816255772,0.7071067807475178)'::s2point::s2cell,
          '8800000000000001'::s2cell,
          's2point_to_s2cell');

select is('(4.3902967226106497e-10,-0.7071067816255772,0.7071067807475178)'::s2point::s2latlng,
          '(0.7853981627765666,-1.570796326174015)'::s2latlng,
          's2point_to_s2latlng');

select is('(0.7853981627765666,-1.570796326174015)'::s2latlng::s2point,
          '(4.3902961088603715e-10,-0.7071067816255772,0.7071067807475179)'::s2point,
          's2latlng_to_s2point');

select is('(0.7853981627765666,-1.570796326174015)'::s2latlng::s2cell,
          '8800000000000001'::s2cell,
          's2latlng_to_s2cell');
    
select * from finish();
rollback;
    
