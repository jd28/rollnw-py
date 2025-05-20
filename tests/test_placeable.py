import rollnw
import pathlib
from rollnw import Placeable

TEST_DATA_DIR = pathlib.Path(__file__).parent / "test_data"


def test_Placeable_default_construct():
    obj = Placeable()
    assert obj.handle().type == rollnw.ObjectType.placeable


def test_Placeable_gff_construct():
    obj = Placeable().from_file(TEST_DATA_DIR / "user/development/arrowcorpse001.utp")
    assert obj.common.resref == "arrowcorpse001"
