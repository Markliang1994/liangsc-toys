--
local ej=require "ejoy2d"
local fw=require "ejoy2d.framework"
local pack=require "ejoy2d.simplepackage"
local sprite=require "ejoy2d.sprite"
local shader=require "ejoy2d.shader.c"
local package,path_pattern="tetris","../res/?"

local game_res=pack.load{
	pattern=path_pattern,
	package	
}

local TetrisDraw={ }

function TetrisDraw:new(o)
	local o=o or { }
	o.BLeft=288
	o.BRight=598	
	o.posInfo={ }
	o.posIndex={ }
	o.spInfo={ }

	o.color={"tetris_4","tetris_9","tetris_10","tetris_13","tetris_11","tetris_7","tetris_12"}
	local i,j=0,0
	for i=1,32 do
		o.posInfo[i],o.posIndex[i]={ },{ }
		o.spInfo[i]={ }
		for j=1,16 do
			o.posInfo[i][j],o.posIndex[i][j]=nil,0
			o.spInfo[i][j]={ }
		end
	end
	setmetatable(o,self)
	self.__index=self
	return o
end

function TetrisDraw:if_border(C,D)
	return C<1 or C>32 or D<1 or D>16
end

function TetrisDraw:bigDraw()
	local i,j=0,0
	local x,y=288,78
	local step=18
	for i=1,32 do
		for j=1,16 do
			if self.posInfo[i][j]==1 then
				self.spInfo[i][j]:ps(x+(j-1)*step,y+(i-1)*step)   --(302,78) is origin point
				self.spInfo[i][j]:draw()
			end
		end
	end
end

function TetrisDraw:ifCanDraw(curB,C,D)
	local i,j=0,0
	for i=1,5 do	
		for j=1,5 do
			if (self:if_border(C+i-1,D+j-1) or self.posInfo[C+i-1][D+j-1]==1) and curB[i][j]==1 then
				return false
			end	
		end
	end
	return true
end

function TetrisDraw:copyState(Blo,A,B,index)
	local i,j=0,0
	local AA,BB=A-1,B-1
	for i=1,5 do
		for j=1,5 do
			if Blo[i][j]==1 then
				self.posInfo[AA+i][BB+j]=Blo[i][j]
				self.posIndex[AA+i][BB+j]=index
				self.spInfo[AA+i][BB+j]=ej.sprite(package,self.color[index])
			end
		end
		BB=B-1
	end
end

function TetrisDraw:addLine(index)
	math.randomseed(os.time())
	local i,j
	for i=2,32 do
		for j=1,16 do
			self.posInfo[i-1][j]=self.posInfo[i][j]  --up shift
			self.posIndex[i-1][j]=self.posIndex[i][j]
			self.spInfo[i-1][j]=self.spInfo[i][j]
		end
	end
	--fill
	for i=1,16 do
		self.posInfo[32][i]=math.random(2)-1
		if self.posInfo[32][i]==1 then	--add spriteb filed
			self.posIndex[32][i]=index
			self.spInfo[32][i]=ej.sprite(package,self.color[self.posIndex[32][i]])
		end
	end
end

function TetrisDraw:testFullLine(i)
	local j;
	for j=1,16 do
		if self.posInfo[i][j]==nil then
			return false,0
		end
	end
	return true,i
end

function TetrisDraw:upDate(lineNum)
	local i,j=0,0
	for i=lineNum,1,-1 do
		for j=1,16 do
			self.posInfo[i+1][j]=self.posInfo[i][j]  --up shift
			self.posIndex[i+1][j]=self.posIndex[i][j]
			self.spInfo[i+1][j]=self.spInfo[i][j]
		end
	end
end

function TetrisDraw:removeLine()
	local i,j=0,0
	local lineVector={ }
	local _,temp=false
	local count=0;
	for i=1,32 do
		_,temp=self:testFullLine(i)
		if _ then    --roll back
			for j=1,16 do
				self.posInfo[i][j]=nil
				self.posIndex[i][j]=0
				self.spInfo[i][j]=nil
			end
			count=count+1
			self:upDate(temp-1)
		end
	end
	return count
end

function TetrisDraw:reset()
	local i,j=0,0
	for i=1,32 do
		for j=1,36 do
			self.posInfo[i][j]=nil
			self.posIndex[i][j]=0
			self.spInfo[i][j]=nil
		end
	end
end

return TetrisDraw
