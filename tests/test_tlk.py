import pathlib
from rollnw import Tlk, LanguageID

TEST_DATA_DIR = pathlib.Path(__file__).parent / "test_data"


def test_language_id_construct():
    tlk = Tlk(LanguageID.english)
    assert tlk.language_id() == LanguageID.english


def test_path_construct():
    tlk = Tlk(TEST_DATA_DIR / "root/lang/en/data/dialog.tlk")
    assert tlk.language_id() == LanguageID.english
    assert tlk[0] == "Bad Strref"
    assert tlk[3] == "Bards"
    tlk.set(3, "Not Bards!")
    assert tlk[3] == "Not Bards!"
    assert tlk.modified()
