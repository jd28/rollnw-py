import rollnw
from rollnw import Sound
import pathlib

TEST_DATA_DIR = pathlib.Path(__file__).parent / "test_data"


def test_sound_default_construct():
    obj = Sound()
    assert obj.handle().type == rollnw.ObjectType.sound


def test_sound_gff_construct():
    obj = Sound().from_file(TEST_DATA_DIR / "user/development/blue_bell.uts")
    assert obj.common.resref == "blue_bell"
