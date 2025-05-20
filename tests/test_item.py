import rollnw
from rollnw import Item
import pathlib

TEST_DATA_DIR = pathlib.Path(__file__).parent / "test_data"


def test_Item_default_construct():
    obj = Item()
    assert obj.handle().type == rollnw.ObjectType.item


def test_Item_gff_construct():
    obj = Item.from_file(TEST_DATA_DIR / "user/development/wduersc004.uti")
    assert obj.common.resref == "wduersc004"
