from west.commands import WestCommand
from west import log

class CustomMouse(WestCommand):
    def __init__(self):
        super().__init__(
            "custom-mouse",
            "Custom mouse module for automatic layer switching",
            ""
        )

    def do_add_parser(self, parser_adder):
        return parser_adder.add_parser(self.name)

    def do_run(self, args, unknown_args):
        log.inf("Custom mouse module is active.")
