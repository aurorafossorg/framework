module aurorafw.core.memory.allocator;

interface Allocator
{
	void[] allocate(size_t size);
	bool deallocate(void[] p);
	bool reallocate(ref void[] p, size_t s);

	@property immutable(uint) alignment() const @safe pure nothrow;
}