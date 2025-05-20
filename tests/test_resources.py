import rollnw
import pathlib

TEST_DATA_DIR = pathlib.Path(__file__).parent / "test_data"


def test_erf_construction():
    erf = rollnw.Erf(TEST_DATA_DIR / "user/hak/hak_with_description.hak")
    assert erf.name() == "hak_with_description.hak"
    assert erf.size() == 1


def test_kernel_service():
    mod = rollnw.kernel.load_module(
        TEST_DATA_DIR / "user/modules/DockerDemo.mod")

    assert rollnw.kernel.resman().contains('nw_chicken.utc')

    data = rollnw.kernel.resman().demand('nw_chicken.utc')
    assert len(data.bytes) > 0
