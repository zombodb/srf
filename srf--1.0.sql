create or replace function srf_c(start int, "end" int) returns setof int language c as 'MODULE_PATHNAME', 'srf_c';
