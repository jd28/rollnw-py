import rollnw
import pathlib
from rollnw import Player

TEST_DATA_DIR = pathlib.Path(__file__).parent / "test_data"


def test_creature_gff_construct():
    player = Player.from_file(
        TEST_DATA_DIR / "user/servervault/CDKEY/testsorcpc1.bic")
    assert player
    assert len(player.history.entries[0].known_spells)
