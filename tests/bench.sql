
CREATE OR REPLACE FUNCTION random_between(low float8, high float8) 
   RETURNS float8 AS
$$
BEGIN
   RETURN random() * (high - low + 1) + low;
END;
$$ language 'plpgsql' STRICT;


SELECT s2latlng(random_between(0, 90), random_between(0, 90), true)::s2cell as cell
    INTO four FROM generate_series(1,1000000);
create index on four using btree(cell);
