
void s2c_id_to_latlng(uint64_t id, double *lat, double *lng) {
    S2Cell cell = S2Cell(S2CellId(id));
    S2LatLng ll = S2LatLng(cell.GetCenter());
    *lat = ll.lat().radians();
    *lng = ll.lng().radians();
}
