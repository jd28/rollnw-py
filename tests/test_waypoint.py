import rollnw
import json
import pytest
import pathlib

TEST_DATA_DIR = pathlib.Path(__file__).parent / "test_data"


@pytest.fixture
def json_file():
    with open(TEST_DATA_DIR / 'user/development/wp_behexit001.utw.json') as f:
        return json.load(f)


def test_waypoint_default_construct():
    w = rollnw.Waypoint()
    assert w.handle().type == rollnw.ObjectType.waypoint


def test_waypoint_dict_construct(json_file):
    w = rollnw.Waypoint.from_dict(json_file)
    assert not w.has_map_note
    assert str(w.common.resref) == 'wp_behexit001'


def test_waypoint_gff_construct():
    w = rollnw.Waypoint.from_file(
        TEST_DATA_DIR / "user/development/wp_behexit001.utw")
    assert not w.has_map_note
    assert str(w.common.resref) == 'wp_behexit001'


def test_waypoint_json_construct():
    w = rollnw.Waypoint.from_file(
        TEST_DATA_DIR / "user/development/wp_behexit001.utw.json")
    assert not w.has_map_note
    assert str(w.common.resref) == 'wp_behexit001'
