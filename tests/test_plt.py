from rollnw import Plt
import rollnw
import pathlib

TEST_DATA_DIR = pathlib.Path(__file__).parent / "test_data"


def test_plt_construct():
    plt = Plt(TEST_DATA_DIR / "user/development/pmh0_head001.plt")
    assert plt.valid()

    color = rollnw.decode_plt_color(plt, rollnw.PltColors(), 0, 0)
    assert color == 0xFF51668B
