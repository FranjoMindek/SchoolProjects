class ReadOnlyList:
    def __init__(self, ref: list):
        self._ref = ref

    def __getitem__(self, item: int):
        return self._ref[item]

    def __len__(self) -> int:
        return len(self._ref)
