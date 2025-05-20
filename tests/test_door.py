from rollnw import Door, ObjectType
import pathlib

TEST_DATA_DIR = pathlib.Path(__file__).parent / "test_data"


def test_door_default_construct():
    obj = Door()
    assert obj.handle().type == ObjectType.door


def test_door_gff_construct():
    obj = Door.from_file(TEST_DATA_DIR / "user/development/door_ttr_002.utd")
    assert obj.common.resref == "door_ttr_002"
