// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ILiveLinkSource.h"
#include "MessageEndpoint.h"
#include "IMessageContext.h"
#include "HAL/ThreadSafeBool.h"

class ILiveLinkClient;
struct FLiveLinkPongMessage;
struct FLiveLinkSubjectDataMessage;
struct FLiveLinkSubjectFrameMessage;
struct FLiveLinkHeartbeatMessage;
struct FLiveLinkClearSubject;

/**
 * 
 */
class SMARTSUIT_API FVirtualProductionSource : public ILiveLinkSource
{
public:
	FVirtualProductionSource(const FText& InSourceType, const FText& InSourceMachineName, const FMessageAddress& InConnectionAddress)
		: ConnectionAddress(InConnectionAddress)
		, SourceType(InSourceType)
		, SourceMachineName(InSourceMachineName)
		, HeartbeatLastSent(0.0)
		, ConnectionLastActive(0.0)
	{}

	virtual void ReceiveClient(ILiveLinkClient* InClient, FGuid InSourceGuid);

	void Connect(FMessageAddress& Address);

	virtual bool IsSourceStillValid();

	virtual bool RequestSourceShutdown();

	virtual FText GetSourceType() const { return SourceType; }
	virtual FText GetSourceMachineName() const { return SourceMachineName; }
	virtual FText GetSourceStatus() const { return SourceStatus; }
	static FVirtualProductionSource* Get() {
		return instance;
	}

	void HandleSubjectData(const FName subjectName, const FLiveLinkRefSkeleton skeleton);
	void HandleSubjectFrame(const FName subjectName, const TArray<FLiveLinkCurveElement>& Message);
	void HandleClearSubject(const FName subjectName);


private:
	TArray<FName> subjectNames;
	// End Message bus message handlers

	ILiveLinkClient* Client;

	// Our identifier in LiveLink
	FGuid SourceGuid;

	//TSharedPtr<FMessageEndpoint, ESPMode::ThreadSafe> MessageEndpoint;

	FMessageAddress ConnectionAddress;

	FText SourceType;
	FText SourceMachineName;
	FText SourceStatus;

	// Time we last sent connection heartbeat
	double HeartbeatLastSent;

	// Time we last recieved anything 
	double ConnectionLastActive;

	// Current Validity of Source
	FThreadSafeBool bIsValid;
	//singleton instance
	static FVirtualProductionSource *instance;

};