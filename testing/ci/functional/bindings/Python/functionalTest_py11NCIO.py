
import unittest
import ncio

class TestNCIO(unittest.TestCase):

    def setUp(self):
        self.ncio = ncio.NCIO(None)

    def test_NCIO(self):
        self.ncio.set_parameter('key', 'value')
        value = self.ncio.get_parameter('key')
        self.assertEqual(value, 'value')

if __name__ == '__main__':
    unittest.main()
