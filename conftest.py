import rollnw
import rollnw.kernel


def pytest_sessionstart(session):
    rollnw.kernel.start()
