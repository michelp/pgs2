\timing on
DROP TABLE IF EXISTS pgs2_bench_cell_btree ;

CREATE OR REPLACE FUNCTION random_between(low float8, high float8) 
   RETURNS float8 AS
$$
BEGIN
   RETURN random() * (high - low + 1) + low;
END;
$$ language 'plpgsql' STRICT;

SELECT s2latlng(random_between(-180, 180), random_between(-90, 90), true)::s2cell as cell
    INTO pgs2_bench_cell_btree FROM generate_series(1, 1000000);

create index on pgs2_bench_cell_btree using btree(cell);
