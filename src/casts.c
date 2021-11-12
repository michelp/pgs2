Datum
S2Point_as_S2Cell(PG_FUNCTION_ARGS) {
    pgs2_S2Point *point;
    pgs2_S2Cell *cell;
    
    point = PGS2_GETARG_S2POINT_P(0);
    cell = palloc0(sizeof(pgs2_S2Cell));
    s2c_xyz_to_id(point->x, point->y, point->z, &(cell->id));
    PGS2_RETURN_S2CELL_P(cell);
}

Datum
S2Point_as_S2LatLng(PG_FUNCTION_ARGS) {
    pgs2_S2Point *point;
    pgs2_S2LatLng *ll;
    
    point = PGS2_GETARG_S2POINT_P(0);
    ll = palloc0(sizeof(pgs2_S2LatLng));
    s2c_xyz_to_latlng(point->x, point->y, point->z, &(ll->x), &(ll->y));
    PGS2_RETURN_S2LATLNG_P(ll);
}

Datum
S2Cell_as_S2Point(PG_FUNCTION_ARGS) {
    pgs2_S2Point *point;
    pgs2_S2Cell *cell;
    
    cell = PGS2_GETARG_S2CELL_P(0);
    point = palloc0(sizeof(pgs2_S2Point));
    s2c_id_to_xyz(cell->id, &(point->x), &(point->y), &(point->z));
    PGS2_RETURN_S2POINT_P(point);
}

Datum
S2Cell_as_S2LatLng(PG_FUNCTION_ARGS) {
    pgs2_S2Cell *cell;
    pgs2_S2LatLng *ll;
    
    cell = PGS2_GETARG_S2CELL_P(0);
    ll = palloc0(sizeof(pgs2_S2LatLng));
    s2c_id_to_latlng(cell->id, &(ll->x), &(ll->y));
    PGS2_RETURN_S2LATLNG_P(ll);
}

Datum
S2LatLng_as_S2Point(PG_FUNCTION_ARGS) {
    pgs2_S2Point *point;
    pgs2_S2Cell *cell;
    
    cell = PGS2_GETARG_S2CELL_P(0);
    point = palloc0(sizeof(pgs2_S2Point));
    s2c_id_to_xyz(cell->id, &(point->x), &(point->y), &(point->z));
    PGS2_RETURN_S2POINT_P(point);
}

Datum
S2LatLng_as_S2Cell(PG_FUNCTION_ARGS) {
    pgs2_S2Point *point;
    pgs2_S2Cell *cell;
    
    cell = PGS2_GETARG_S2CELL_P(0);
    point = palloc0(sizeof(pgs2_S2Point));
    s2c_id_to_xyz(cell->id, &(point->x), &(point->y), &(point->z));
    PGS2_RETURN_S2POINT_P(point);
}

