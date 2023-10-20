import Binary
import unittest

# create subclass of unittest
class TestBinary(unittest.TestCase):

    @classmethod
    def setUpClass(self):
        self.xOr = {
            "test1": ["10101", "11101", "01000"],
            "test2": ["10111", "11111", "01000"],
            "test3": ["1011101011", "1111110010", "0100011001"],
        }

    def test_bit_to_dec(self):
        self.assertEqual(Binary.bit_to_dec("100101"),37, "bit_to_dec failed")

    def test_shiftbits(self):
        self.assertEqual(Binary.shiftbits("10010101",3,'l'), "10101100", "Incorrect shift direction or amount")

    def test_xOr(self):

        for keys in self.xOr:
            with self.subTest():
                self.assertEqual(Binary.xOr(self.xOr[keys][0], self.xOr[keys][1]), self.xOr[keys][2])

    def test_hex2bin(self):
        self.assertEqual(Binary.hex2bin("AB0998"), "101010110000100110011000")

    def test_bin2hex(self):
        self.assertEqual(Binary.bin2hex("10101101"), "AD")

    def test_Dec_to_Bin(self):
        self.assertEqual(Binary.Dec_to_Bin(10), "1010")

    def test_txttoBits(self):
        self.assertEqual(Binary.txttoBits("ab"), "0110000101100010")

        
        
unittest.main()