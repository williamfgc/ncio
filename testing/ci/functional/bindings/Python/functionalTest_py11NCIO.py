
import unittest
import ncio
import ncio.schema.nexus as nexus

class TestNCIO(unittest.TestCase):

    def setUp(self):
        self.ncio = ncio.NCIO(None)

    def test_NCIO(self):
        self.ncio.set_parameter('key', 'value')
        self.assertEqual(self.ncio.get_parameter('key'), 'value')
        self.assertEqual(self.ncio.get_parameter('null'), None)
        
        bank_id = nexus.entry.bank1_events.event_id
        print(bank_id)
        

if __name__ == '__main__':
    unittest.main()
