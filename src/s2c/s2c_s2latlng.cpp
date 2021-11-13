
void s2c_cell_to_latlng(pgs2_S2Cell *cell, pgs2_S2LatLng *ll, error_cb cb) {
    try {
        S2Cell C = S2Cell(S2CellId(cell->id));
        S2LatLng L = S2LatLng(C.GetCenter());
        ll->lat = L.lat().radians();
        ll->lng = L.lng().radians();
    } CATCH_ALL(cb)
}

void s2c_latlng_to_cell(pgs2_S2LatLng *ll, pgs2_S2Cell *cell, error_cb cb) {
    try {
        S2Cell C = S2Cell(S2LatLng::FromRadians(ll->lat, ll->lng));
        cell->id = C.id().id();
    } CATCH_ALL(cb)
}

void s2c_latlng_to_point(pgs2_S2LatLng *ll, pgs2_S2Point *point, error_cb cb) {
    try {
        S2Point P = S2LatLng::FromRadians(ll->lat, ll->lng).ToPoint();
        point->x = P.x();
        point->y = P.y();
        point->z = P.z();
    } CATCH_ALL(cb)
}
