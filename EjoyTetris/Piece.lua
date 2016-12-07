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

local Piece=require "script.TetrisPiece"
local color={"tetris_4","tetris_9","tetris_10","tetris_13","tetris_11","tetris_7","tetris_12"}
local set={ "tetris_14","tetris_15","tetris_16","tetris_17","tetris_19","tetris_18","tetris_20" }
local step=18

function Piece:CopyValue(o,index,subIndex)
	local i,j=0,0
	for i=1,5 do
		o[i]={ }
		for j=1,5 do
			o[i][j]=Piece[index][subIndex][i][j]
		end
	end
	return o
end

function Piece:createPiece(indexA,subIndex,x,y)	
	local o={ }
	o=self:CopyValue(o,indexA,subIndex)
	local i,j=0
	o.x=x
	o.y=y
	o.spInfo={ }
	for i=1,5 do
		o.spInfo[i]={ }
		for j=1,5 do
			o.spInfo[i][j]={ }
		end
	end
	self.isNewPiece=true
	setmetatable(o,self)
	self.__index=self
	return o
end

function Piece:rotate(index,subIndex)
	if subIndex==4 then
		return Piece:createPiece(index,1,self.x,self.y),1
	end
	return Piece:createPiece(index,subIndex+1,self.x,self.y),subIndex+1
end

function Piece:moveLeft(index)
	self.x=self.x-18
	self:draw(index)
end

function Piece:moveRight(index)
	self.x=self.x+18
	self:draw(index)
end

function Piece:moveDown(index)
	self.y=self.y+18
	self:draw(index)
end

function Piece:drawCurB(index)
	local i,j
	if self.isNewPiece then
		for i=1,5 do
			for j=1,5 do
				if self[i][j]==1 then
					self.spInfo[i][j]=ej.sprite(package,color[index])
				end
			end
		end
	end
	--draw
	for i=1,5 do
		for j=1,5 do
			if self[i][j]==1 then
				self.spInfo[i][j]:ps(self.x+(j-1)*18,self.y+(i-1)*18)
				self.spInfo[i][j]:draw()
			end
		end
	end
	self.isNewPiece=false
end

function Piece:drawNextB(index)
	local spn=ej.sprite(package,set[index])
	spn:ps(self.x,self.y)
	spn:draw()
end

function Piece:draw(index)
	if self.x==637 and self.y==220 then
		self:drawNextB(index)
		return 
	end
	self:drawCurB(index)
end

return Piece
