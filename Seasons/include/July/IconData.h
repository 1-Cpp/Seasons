
class IconData
{
public:
	int width = 32 ;
	int height = 32;
	int paletteColorCount = 0;
	int colorPlanes = 0; // could be 1
	int bitsPerPixel = 1; // maybe zero in some cases when this can be calculated
	unsigned int dataSize = 0;
	IconData();
	virtual ~IconData();
};
