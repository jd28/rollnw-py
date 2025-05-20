import rollnw
from rollnw import Encounter
import pathlib

TEST_DATA_DIR = pathlib.Path(__file__).parent / "test_data"


def test_encounter_default_construct():
    obj = Encounter()
    assert obj.handle().type == rollnw.ObjectType.encounter


def test_encounter_gff_construct():
    obj = Encounter.from_file(
        TEST_DATA_DIR / "user/development/boundelementallo.ute")
    assert obj.common.resref == "boundelementallo"
