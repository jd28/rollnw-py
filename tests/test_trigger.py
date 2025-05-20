import rollnw
from rollnw import Trigger
import pathlib

TEST_DATA_DIR = pathlib.Path(__file__).parent / "test_data"


def test_Trigger_default_construct():
    obj = Trigger()
    assert obj.handle().type == rollnw.ObjectType.trigger


def test_Trigger_gff_construct():
    obj = Trigger.from_file(
        TEST_DATA_DIR / "user/development/newtransition001.utt")
    assert obj.common.resref == "newtransition001"
