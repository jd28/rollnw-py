from rollnw import Dialog, LanguageID
import pathlib

TEST_DATA_DIR = pathlib.Path(__file__).parent / "test_data"


def test_dialog_gff_construct():
    dlg = Dialog.from_file(TEST_DATA_DIR / "user/development/alue_ranger.dlg")
    assert len(dlg) == 2
    ptr = dlg.add_string("Hello there")
    assert len(dlg) == 3
    assert dlg[2].node.text.get(LanguageID.english) == "Hello there"
    dlg[2].node.text.add(LanguageID.english, "Goodbye there")
    assert dlg[2].node.text.get(LanguageID.english) == "Goodbye there"
    dlg.save("bin/alue_ranger.dlg")
    dlg.save("bin/alue_ranger.dlg.json")
