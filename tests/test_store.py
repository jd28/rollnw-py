import rollnw
from rollnw import Store
import pathlib

TEST_DATA_DIR = pathlib.Path(__file__).parent / "test_data"


def test_Store_default_construct():
    obj = Store()
    assert obj.handle().type == rollnw.ObjectType.store


def test_Store_gff_construct():
    obj = Store.from_file(TEST_DATA_DIR / "user/development/storethief002.utm")
    assert obj.common.resref == "storethief002"
